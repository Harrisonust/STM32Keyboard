
# CMake Project File
#
# If you're changing CMake stuff and it doesnt seem to change, delete the CMakeCache.txt file and retry
#
# For Windows, CMake tries to use Visual Studio if available, this fucks up the custom toolchain setting in here
# Always manually override to Ninja or Make
#
# For all platforms Ninja is much faster than Make so use it

cmake_minimum_required(VERSION 3.0)

include(project.cmake OPTIONAL RESULT_VARIABLE PROJ_FILE_EXISTS)
if(NOT PROJ_FILE_EXISTS)
	message(FATAL_ERROR "No Project Config (project.cmake)")
else()
	user_proj_config()
endif()

if(NOT DEFINED STM32FXXX OR STM32FXXX STREQUAL "")
	message(FATAL_ERROR "Define which STM32 MCU you are using in project.cmake (set STM32FXXX)")
endif()

if (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
	message("CMAKE_BUILD_TYPE defaulting to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

if (NOT DEFINED CMAKE_VERBOSE_MAKEFILE)
	set(CMAKE_VERBOSE_MAKEFILE OFF)
endif()

if(APPLE)
	find_program(STM32CubeProg "STM32_Programmer_CLI"
		"/Applications/STMicroelectronics/STM32Cube/STM32CubeProgrammer/STM32CubeProgrammer.app/Contents/MacOs/bin")
	# set(prog "/Applications/STMicroelectronics/STM32Cube/STM32CubeProgrammer/STM32CubeProgrammer.app/Contents/MacOs/bin/STM32_Programmer_CLI")
else()
	find_program(STM32CubeProg "STM32_Programmer_CLI"
		"C:/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin"
		"C:/Program Files/STMicroelectronics/STM32CubeProgrammer/bin")
	# set(prog "STM32_Programmer_CLI")
endif()
find_program(STLINKUTIL "st-link_cli")
find_program(OPENOCD_EXE "openocd")
find_program(STFLASH_EXE "st-flash")
if(WIN32)
	find_program(STMFlashLoader "STMFlashLoader.exe"
		"C:/Program Files/STMicroelectronics/Software/Flash Loader Demo/"
		"C:/Program Files (x86)/STMicroelectronics/Software/Flash Loader Demo/")
endif()

if (NOT DEFINED XTAL)
	set(XTAL 8000000)
endif()

function(join VALUES GLUE OUTPUT)
  string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

##############################################################################################################################################################################

string(TOLOWER ${STM32FXXX} stm32fxxx)
string(TOUPPER ${STM32FXXX} STM32FXXX)
message("STM32Fxyzab: ${STM32FXXX}")

# Determine STM32FXXX family
string(REGEX MATCH "^(STM32[FLHG][0-9])" STM32_FAMILY "${STM32FXXX}")
string(TOLOWER ${STM32_FAMILY} stm32_family)
message("STM32Fx Family: ${STM32_FAMILY}")

# Determine STM32FXXX series
string(REGEX MATCH "^(STM32[FLHG][0-9][0-9][0-9])" STM32_SERIES "${STM32FXXX}")
message("STM32Fxxx Series: ${STM32_SERIES}")
string(TOLOWER ${STM32_SERIES} stm32_series)

string(REGEX MATCH "^(STM32[FLHG][0-9][0-9][0-9])([A-Z])([A-Z0-9])" CPU_FAMILY_MATCH "${STM32FXXX}")
set(STM32_SERIES_A "${CMAKE_MATCH_1}x${CMAKE_MATCH_3}")
set(STM32_SERIES_B "${CMAKE_MATCH_1}${CMAKE_MATCH_2}x")
string(TOLOWER ${STM32_SERIES_A} stm32_series_a)
string(TOLOWER ${STM32_SERIES_B} stm32_series_b)
message("${STM32_SERIES_A}/${STM32_SERIES_B}")

# Set CPU type for compiler
# TODO: F0, F2, F7, H7
if(${STM32_FAMILY} STREQUAL "STM32F1")
	set(GCC_CPU "cortex-m3")
	set(ARMCC_CPU "Cortex-M3")
	set(DEF_ARM_MATH -DARM_MATH_CM3 -Dnum_t=float)
	set(HAS_FPU 0)
elseif(${STM32_FAMILY} STREQUAL "STM32F4" OR ${STM32_FAMILY} STREQUAL "STM32F3")
	set(GCC_CPU "cortex-m4")
	set(ARMCC_CPU "Cortex-M4.fp")
	set(DEF_ARM_MATH -DARM_MATH_CM4 -Dnum_t=float -DHAS_FLOAT)
	set(HAS_FPU 1)
	set(GCC_FPU fpv4-sp-d16)
	set(SP_FPU 1)
elseif(${STM32_FAMILY} STREQUAL "STM32H7")
	set(GCC_CPU "cortex-m7")
	set(ARMCC_CPU "Cortex-M7.fp.dp")
	set(DEF_ARM_MATH -DARM_MATH_CM7 -Dnum_t=double -DHAS_DOUBLE)
	set(HAS_FPU 1)
	set(GCC_FPU fpv5-d16)
elseif(${STM32_FAMILY} STREQUAL "STM32F0")
	set(GCC_CPU "cortex-m0")
	set(ARMCC_CPU "Cortex-M0")
	set(DEF_ARM_MATH -DARM_MATH_CM0 -Dnum_t=float)
	set(HAS_FPU 0)
else()
	message(FATAL_ERROR "Unrecognised device family: ${STM32_FAMILY}")
endif()

set(STM32_DEFINES ${DEF_ARM_MATH} 
	-Dstm32header="${stm32_family}xx.h" -DSTM32_MCU=${STM32FXXX} -DSTM32_SERIES=${STM32_SERIES} -DSTM32_FAMILY=${STM32_FAMILY}
	-D${STM32FXXX} -D${STM32_SERIES}xx -D${STM32_FAMILY} -D${STM32_SERIES_A} -D${STM32_SERIES_B} -D${STM32_SERIES_A} -D${STM32_SERIES_B})
if (STM32_SERIES STREQUAL STM32F405)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F40_41xxx)
elseif (STM32_SERIES STREQUAL STM32F415)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F40_41xxx)
elseif (STM32_SERIES STREQUAL STM32F407)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F40_41xxx)
elseif (STM32_SERIES STREQUAL STM32F417)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F40_41xxx)
elseif (STM32_SERIES STREQUAL STM32F427)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F427_437xx)
elseif (STM32_SERIES STREQUAL STM32F437)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F427_437xx)
elseif (STM32_SERIES STREQUAL STM32F429)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F429_439xx)
elseif (STM32_SERIES STREQUAL STM32F439)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F429_439xx)
elseif (STM32_SERIES STREQUAL STM32F401) #xC
elseif (STM32_SERIES STREQUAL STM32F401) #xE
elseif (STM32_SERIES STREQUAL STM32F410) #Tx
elseif (STM32_SERIES STREQUAL STM32F410) #Cx
elseif (STM32_SERIES STREQUAL STM32F410) #Rx
elseif (STM32_SERIES STREQUAL STM32F411) #xE
elseif (STM32_SERIES STREQUAL STM32F446)
elseif (STM32_SERIES STREQUAL STM32F469)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F469_479xx)
elseif (STM32_SERIES STREQUAL STM32F479)
	set(STM32_DEFINES ${STM32_DEFINES} -DSTM32F469_479xx)
elseif (STM32_SERIES STREQUAL STM32F412) #Cx
elseif (STM32_SERIES STREQUAL STM32F412) #Zx
elseif (STM32_SERIES STREQUAL STM32F412) #Rx
elseif (STM32_SERIES STREQUAL STM32F412) #Vx
elseif (STM32_SERIES STREQUAL STM32F413)
elseif (STM32_SERIES STREQUAL STM32F423)
endif()

if (NOT DEFINED OPENOCD_CFG)
	find_file(OPENOCD_CFG_FILE "openocd.cfg" "." "./src" "${CMAKE_BINARY_DIR}"
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(OPENOCD_CFG_FILE "${stm32_family}x.cfg" "." "./src" "${CMAKE_BINARY_DIR}"
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	if (OPENOCD_CFG_FILE)
		set(OPENOCD_CFG -f ${OPENOCD_CFG_FILE})
		message("Found openocd.cfg: ${OPENOCD_CFG_FILE}")
	else()
		set(OPENOCD_CFG -f interface/stlink-v2.cfg -f target/${stm32_family}x.cfg)
	endif()
endif()

if (NOT DEFINED MCU_STARTUP_FILE)
	set(MCU_STARTUP_SEARCH_DIRS
		"." "./MDK-ARM" "./Startup"
		"./startup/GCC" "./startup" 
		"./lib/f4/startup/GCC" "./lib/f4/startup")
	message("Looking for Startup Assembly in ${MCU_STARTUP_SEARCH_DIRS}")
	find_file(MCU_STARTUP_FILE "startup_${stm32fxxx}.s" ${MCU_STARTUP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(MCU_STARTUP_FILE "startup_${stm32_series_b}.s" ${MCU_STARTUP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(MCU_STARTUP_FILE "startup_${stm32_series_a}.s" ${MCU_STARTUP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(MCU_STARTUP_FILE "startup_${stm32_series}xx.s" ${MCU_STARTUP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(MCU_STARTUP_FILE "startup_${stm32_family}xx.s" ${MCU_STARTUP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(MCU_STARTUP_FILE "startup_${stm32fxxx}tx.s" ${MCU_STARTUP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	message("startup files found ${MCU_STARTUP_FILE}")
	if (CUBE_PROJECT OR CUBE_PROJECT_LL)
		file(GLOB MCU_STARTUP_FILE "startup_*.s")
	endif()
endif()

set(MCU_STARTUP_FILE startup_stm32f103xb.s)

if (MCU_STARTUP_FILE)
	message("MCU_STARTUP_FILE: ${MCU_STARTUP_FILE}")
else()
	message(FATAL_ERROR "Could not find a startup file")
endif()

if (NOT LINKER_SCRIPT)
	set(MEMMAP_SEARCH_DIRS
		"." "./MDK-ARM" 
		"./lib/f4/mem" "./src/mem")
	message("Looking for Linker Script in ${MEMMAP_SEARCH_DIRS}")
	find_file(LINKER_SCRIPT "${STM32FXXX}.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32_SERIES_B}.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32_SERIES_A}.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32_SERIES}.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32_FAMILY}.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32FXXX}Tx_FLASH.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32_SERIES_B}Tx_FLASH.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_file(LINKER_SCRIPT "${STM32_SERIES_A}Tx_FLASH.ld" ${MEMMAP_SEARCH_DIRS}
		NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)

	if (CUBE_PROJECT OR CUBE_PROJECT_LL)
		file(GLOB LINKER_SCRIPT "${STM32_FAMILY}*.ld")
	endif()
endif()
if (NOT LINKER_SCRIPT)
	message(FATAL_ERROR "Could not find a linker script")
else()
	message("LINKER_SCRIPT: ${LINKER_SCRIPT}")
endif()

if (NOT DEFINED XTAL)
	set(XTAL 8000000)
endif()

set(USER_DEFINES ${USER_DEFINES} -DHSE_VALUE=${XTAL})
if (NOT DEFINED USE_STM_DRIVER)
	if (DEFINED CUBE_PROJECT)
		set(USER_DEFINES ${USER_DEFINES} -DUSE_HAL_DRIVER)
	elseif (DEFINED CUBE_PROJECT_LL)
		set(USER_DEFINES ${USER_DEFINES} -DUSE_LL_DRIVER -DUSE_FULL_LL_DRIVER)
	else()
		set(USER_DEFINES ${USER_DEFINES} -DUSE_STDPERIPH_DRIVER)
	endif()
else()
	set(USER_DEFINES ${USER_DEFINES} -D${USE_STM_DRIVER})
endif()
message("USER_DEFINES = ${USER_DEFINES}")

if (NOT DEFINED SOURCE_FILES)
	if (DEFINED CUBE_PROJECT OR DEFINED CUBE_PROJECT_LL)
		file(GLOB_RECURSE MIDDLEWARE_SOURCES "./Middlewares/*.c")
		file(GLOB SOURCE_FILES "./Drivers/${STM32_FAMILY}xx_HAL_Driver/Src/*.c" "./USB_DEVICE/*/*.c" "./Core/Src/oled/*.c" "./Core/Src/*.c")
		set(SOURCE_FILES ${SOURCE_FILES} ${MIDDLEWARE_SOURCES} ${ADD_SOURCE_FILES})
	elseif (DEFINED SOURCE_DIR)
		file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c")
	else()
		file(GLOB_RECURSE SOURCE_FILES "lib/f4/*.cpp" "src/*.cpp" "lib/f4/*.c" "src/*.c")
	endif()
endif()
join("${SOURCE_FILES}" "\n -" PRINT_SRC_FILES)
message("SOURCE_FILES = \n -${PRINT_SRC_FILES}")

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
	IF(IS_DIRECTORY ${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

if (NOT DEFINED INCLUDE_DIRS)
	if (DEFINED CUBE_PROJECT OR DEFINED CUBE_PROJECT_LL)
		file(GLOB_RECURSE MIDDLEWARE_INCLUDES LIST_DIRECTORIES true
		"./Middlewares/*/Inc" "./Middlewares/*/Include"  
		"./Middlewares/*/include" "./Middlewares/*/CMSIS_RTOS" 
		"./Middlewares/*/ARM_CM3")
		file(GLOB_RECURSE DRIVERS_INCLUDES LIST_DIRECTORIES true "./Drivers/*/Inc" "./Drivers/*/Include")
		file(GLOB_RECURSE CMSIS_INCLUDES LIST_DIRECTORIES true "./CMSIS/*/Inc" "./CMSIS/*/Include")
		file(GLOB_RECURSE CORE_INCLUDES LIST_DIRECTORIES true "./Core/Inc" "./Core/Inc/oled")
		file(GLOB_RECURSE USB_INCLUDES LIST_DIRECTORIES true "./USB_DEVICE/App" "./USB_DEVICE/Target")
		# file(GLOB_RECURSE DRIVER_INCLUDES LIST_DIRECTORIES true "./Drivers/*/Inc")
		set(INCLUDE_DIRS 
			${ADD_INCLUDE_DIRS}
			./Inc/
			${CORE_INCLUDES}
			${MIDDLEWARE_INCLUDES}
			${DRIVERS_INCLUDES}
			${CMSIS_INCLUDES}
			${USB_INCLUDES}
		)
		
	elseif (DEFINED SOURCE_DIR)
		file(GLOB INCLUDE_DIRS "${SOURCE_DIR}/*/")
	else()
		file(GLOB INCLUDE_DIRS "./src/*/")
		SUBDIRLIST(SUBDIRS "lib/f4")
		list(APPEND INCLUDE_DIRS ${SUBDIRS})
		list(FILTER INCLUDE_DIRS EXCLUDE REGEX ".*DS_Store$")
	endif()
endif()
join("${INCLUDE_DIRS}" "\n -" PRINT_INC_DIRS)
message("INCLUDE_DIRS = \n -${PRINT_INC_DIRS}")

if (NOT DEFINED LINK_LIBRARIES)
	set(STATIC_LIB_EXT "a")

	if (DEFINED CUBE_PROJECT OR DEFINED CUBE_PROJECT_LL)
		file(GLOB LINK_LIBRARIES "./Src/*.${STATIC_LIB_EXT}")
	elseif(DEFINED STATICLIB_DIR)
		file(GLOB LINK_LIBRARIES "${STATICLIB_DIR}/GCC/*.${STATIC_LIB_EXT}")
	else()
		file(GLOB LINK_LIBRARIES "./lib/f4/math/lib/GCC/*.${STATIC_LIB_EXT}")
	endif()
endif()
set(LINK_LIBRARIES ${LINK_LIBRARIES} ${ADD_LINK_LIBRARIES})
message("LINK_LIBRARIES (${STATIC_LIB_EXT}) = ${LINK_LIBRARIES}")

##############################################################################################################################################################################

## Compiler Toolchain Definitions

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${GCC_CPU})
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_CROSSCOMPILING TRUE)

	# SET(CMAKE_C_COMPILER_WORKS 1)
	SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
	SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
	find_program(AS arm-none-eabi-as)
	find_program(AR arm-none-eabi-ar)
	find_program(OBJCOPY arm-none-eabi-objcopy)
	find_program(OBJDUMP arm-none-eabi-objdump)
	find_program(OBJSIZE arm-none-eabi-size)

	# set(CMAKE_SYSROOT ${GCC_DIR}/..)
	# set(CMAKE_FIND_ROOT_PATH ${GCC_DIR}/..)

# TODO: WTF?
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

##############################################################################################################################################################################

if (NOT DEFINED PROJ_NAME)
	set(PROJ_NAME "Project")
endif()

## Start CMake Project
project (${PROJ_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
enable_language(C CXX ASM)

message("Generating project: ${PROJECT_NAME} for ${STM32FXXX}-${CMAKE_BUILD_TYPE}")

add_executable(${PROJECT_NAME} ${MCU_STARTUP_FILE} ${SOURCE_FILES})

	set(COMP_DEFINES -D__pure=__attribute__\(\(const\)\) -D__forceinline=__attribute__\(\(always_inline\)\) -D__value_in_regs= -D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\))

	set(COMPILER_INFO_FLAGS -g)
	set(TIME_OPT_FLAGS -O3) 
	if(USE_LTO)
		set(TIME_OPT_FLAGS ${TIME_OPT_FLAGS} -flto -Wl,--undefined=vTaskSwitchContext)
		set(LINKER_OPT_FLAGS ${LINKER_OPT_FLAGS} -flto -Wl,--undefined=vTaskSwitchContext)
	endif()
	if(USE_OFAST)
		set(TIME_OPT_FLAGS ${TIME_OPT_FLAGS} -Ofast)
	endif()
	set(SPACE_OPT_FLAGS -Os)
	set(DEBUG_OPT_FLAGS -Og)

	SET(COMMON_FLAGS -mcpu=${GCC_CPU} -mthumb -mthumb-interwork -fno-math-errno)
	if(NOT DEFINED EN_STRICT_ALIASING OR STRICT_ALIASING EQUAL 0)
		SET(COMMON_FLAGS ${COMMON_FLAGS} -fno-strict-aliasing)
	endif()
	if (DEFINED GCC_FPU)
		set(COMMON_FLAGS ${COMMON_FLAGS} -mfloat-abi=hard -mfpu=${GCC_FPU})
	else()
		set(COMMON_FLAGS ${COMMON_FLAGS} -mfpu=vfp -msoft-float)
	endif()
	if(NOT DEFINED GCC_SPECS)
		if (DEFINED CUBE_PROJECT OR DEFINED CUBE_PROJECT_LL)
			set(COMMON_FLAGS ${COMMON_FLAGS} -specs=nosys.specs -specs=nano.specs)
		else()
			set(COMMON_FLAGS ${COMMON_FLAGS} -specs=nosys.specs)
		endif()
	else()
		set(COMMON_FLAGS ${COMMON_FLAGS} -specs=${GCC_SPECS})
	endif()

	# -Werror=cast-qual
	SET(GCC_WARN_FLAGS_C -Werror=discarded-qualifiers -Werror=incompatible-pointer-types -Werror=implicit-int -Werror=int-conversion -Werror=implicit-function-declaration)
	SET(GCC_WARN_FLAGS -Wall -Werror=restrict -Werror=maybe-uninitialized -Wno-comment -Werror=return-type -Werror=cast-qual -Wno-unused-parameter -Wno-attributes -Wno-unused-function -Wno-unknown-pragmas)
	if (DEFINED STFU_GCC AND STFU_GCC EQUAL 1)
		SET(GCC_WARN_FLAGS ${GCC_WARN_FLAGS} -w)
	elseif(DEFINED WHINE_GCC AND WHINE_GCC EQUAL 1)
		SET(GCC_WARN_FLAGS_C ${GCC_WARN_FLAGS_C} -Wstrict-prototypes)
		SET(GCC_WARN_FLAGS ${GCC_WARN_FLAGS} 
			-Wextra -Wno-missing-field-initializers -Wcast-align
			-Wfloat-equal -Wunreachable-code -Wundef 
			-Wwrite-strings -Wswitch-default -Wswitch-enum
			-Wuninitialized -Winit-self -Wtype-limits) #-Wconversion
	endif()
	if (GCC_FATAL_ERRORS)
		set(GCC_WARN_FLAGS ${GCC_WARN_FLAGS} -Wfatal-errors)
	endif()
	# fshort-enums, -fdollars-in-identifiers
	SET(GCC_FEAT_FLAGS_C -fplan9-extensions)
	SET(GCC_FEAT_FLAGS -g -fverbose-asm -fshort-enums #[[-fno-builtin-malloc]] -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-common -freg-struct-return)
	if (SP_FPU)
		set(GCC_FEAT_FLAGS ${GCC_FEAT_FLAGS} -fsingle-precision-constant -Werror=double-promotion)
	endif()
	SET(COMPILER_FLAGS ${COMMON_FLAGS} ${GCC_WARN_FLAGS} ${GCC_FEAT_FLAGS})

	SET(C_FLAGS ${GCC_WARN_FLAGS_C} ${GCC_FEAT_FLAGS_C} -Dauto=__auto_type)
	SET(CPP_FLAGS -fno-exceptions -fno-non-call-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics  -fconcepts) #code sucks to much for -Weffc++
	
	set(LIST_CMAKE_C_FLAGS ${C_FLAGS} ${COMPILER_FLAGS})
	set(LIST_CMAKE_C_FLAGS_DEBUG ${DEBUG_OPT_FLAGS} ${COMPILER_INFO_FLAGS})
	set(LIST_CMAKE_C_FLAGS_MINSIZEREL ${SPACE_OPT_FLAGS})
	set(LIST_CMAKE_C_FLAGS_RELEASE ${TIME_OPT_FLAGS} -funroll-loops) #ftracer, fpeel-loops, -funswitch-loops
	set(LIST_CMAKE_C_FLAGS_RELWITHDEBINFO ${TIME_OPT_FLAGS} ${COMPILER_INFO_FLAGS})
	set(LIST_CMAKE_ASM_FLAGS ${COMMON_FLAGS})
	set(LIST_CMAKE_ASM_FLAGS_DEBUG)
	set(LIST_CMAKE_ASM_FLAGS_MINSIZEREL)
	set(LIST_CMAKE_ASM_FLAGS_RELEASE)
	set(LIST_CMAKE_ASM_FLAGS_RELWITHDEBINFO)
	set(LIST_CMAKE_CXX_FLAGS ${CPP_FLAGS} ${COMPILER_FLAGS})
	set(LIST_CMAKE_CXX_FLAGS_DEBUG ${DEBUG_OPT_FLAGS} ${COMPILER_INFO_FLAGS})
	set(LIST_CMAKE_CXX_FLAGS_MINSIZEREL ${SPACE_OPT_FLAGS})
	set(LIST_CMAKE_CXX_FLAGS_RELEASE ${TIME_OPT_FLAGS} -funroll-loops)
	set(LIST_CMAKE_CXX_FLAGS_RELWITHDEBINFO ${TIME_OPT_FLAGS} ${COMPILER_INFO_FLAGS})
	SET(LIST_CMAKE_EXE_LINKER_FLAGS -Wl,-gc-sections -T \"${LINKER_SCRIPT}\" -Wl,-Map="${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map",--cref)
	set(LIST_CMAKE_EXE_LINKER_FLAGS_DEBUG ${LINKER_INFO_FLAGS})
	set(LIST_CMAKE_EXE_LINKER_FLAGS_MINSIZEREL )
	set(LIST_CMAKE_EXE_LINKER_FLAGS_RELEASE ${LINKER_OPT_FLAGS})
	set(LIST_CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${LINKER_INFO_FLAGS})

	# target_sources(${PROJECT_NAME} PUBLIC ${LINKER_SCRIPT})

	# get_target_property(_cur_link_deps ${PROJECT_NAME} LINK_DEPENDS)
    # string(APPEND _cur_link_deps ${LINKER_SCRIPT})
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")

	set(ALL_DEFINES ${USER_DEFINES} ${COMP_DEFINES} ${STM32_DEFINES})

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
	    COMMENT "Building HEX File")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
	    COMMENT "Building BIN File")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${OBJDUMP} -d -r -S -l -w -marmv7 ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lst
	    COMMENT "Dumping Assembly Listing")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${OBJDUMP} -d -S -marmv7 ${PROJECT_NAME}.elf > ${PROJECT_NAME}.s
	    COMMENT "Dumping Assembly Listing")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${OBJSIZE} -A -d ${PROJECT_NAME}.elf
		COMMENT "Object Size:")

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    SUFFIX ".elf"
)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${ALL_DEFINES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})

join("${LIST_CMAKE_C_FLAGS}" " " CMAKE_C_FLAGS)
join("${LIST_CMAKE_C_FLAGS_DEBUG}" " " CMAKE_C_FLAGS_DEBUG)
join("${LIST_CMAKE_C_FLAGS_MINSIZEREL}" " " CMAKE_C_FLAGS_MINSIZEREL)
join("${LIST_CMAKE_C_FLAGS_RELEASE}" " " CMAKE_C_FLAGS_RELEASE)
join("${LIST_CMAKE_C_FLAGS_RELWITHDEBINFO}" " " CMAKE_C_FLAGS_RELWITHDEBINFO)
join("${LIST_CMAKE_ASM_FLAGS}" " " CMAKE_ASM_FLAGS)
join("${LIST_CMAKE_ASM_FLAGS_DEBUG}" " " CMAKE_ASM_FLAGS_DEBUG)
join("${LIST_CMAKE_ASM_FLAGS_MINSIZEREL}" " " CMAKE_ASM_FLAGS_MINSIZEREL)
join("${LIST_CMAKE_ASM_FLAGS_RELEASE}" " " CMAKE_ASM_FLAGS_RELEASE)
join("${LIST_CMAKE_ASM_FLAGS_RELWITHDEBINFO}" " " CMAKE_ASM_FLAGS_RELWITHDEBINFO)
join("${LIST_CMAKE_CXX_FLAGS}" " " CMAKE_CXX_FLAGS)
join("${LIST_CMAKE_CXX_FLAGS_DEBUG}" " " CMAKE_CXX_FLAGS_DEBUG)
join("${LIST_CMAKE_CXX_FLAGS_MINSIZEREL}" " " CMAKE_CXX_FLAGS_MINSIZEREL)
join("${LIST_CMAKE_CXX_FLAGS_RELEASE}" " " CMAKE_CXX_FLAGS_RELEASE)
join("${LIST_CMAKE_CXX_FLAGS_RELWITHDEBINFO}" " " CMAKE_CXX_FLAGS_RELWITHDEBINFO)
join("${LIST_CMAKE_EXE_LINKER_FLAGS}" " " CMAKE_EXE_LINKER_FLAGS)
join("${LIST_CMAKE_EXE_LINKER_FLAGS_DEBUG}" " " CMAKE_EXE_LINKER_FLAGS_DEBUG)
join("${LIST_CMAKE_EXE_LINKER_FLAGS_MINSIZEREL}" " " CMAKE_EXE_LINKER_FLAGS_MINSIZEREL)
join("${LIST_CMAKE_EXE_LINKER_FLAGS_RELEASE}" " " CMAKE_EXE_LINKER_FLAGS_RELEASE)
join("${LIST_CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}" " " CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO)

##############################################################################################################################################################################

if (CMAKE_HOST_WIN32)
	message("WINDOWS")
	add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
		COMMAND echo * > .gitignore)
else()
	message("NOT WINDOWS")
	add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
		COMMAND touch .gitignore && echo '*' > .gitignore)
endif()

find_file(GDB_DEBUG_FILE "../debug.gdb" "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}"
	NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH)

function(stlinkutil_targets)
	if(STLINKUTIL)
		add_custom_target(flash_stlinkutil
			${STLINKUTIL} -c -P ${PROJECT_NAME}.hex -Rst -Run
			DEPENDS ${PROJECT_NAME}
			COMMENT "Flashing target hardware (by STLink Utility CLI)")

		add_custom_target(erase_stlinkutil
			${STLINKUTIL} -c -ME
			COMMENT "Mass Erase all flash sectors")

		set(FLASH_TARGET flash_stlinkutil PARENT_SCOPE)
		set(ERASE_TARGET erase_stlinkutil PARENT_SCOPE)
	endif()
endfunction()

function(stflash_targets)
	if(STFLASH_EXE)
		add_custom_target(flash_stflash
			${STFLASH_EXE} --reset --format ihex write ${PROJECT_NAME}.hex
			DEPENDS ${PROJECT_NAME}
			COMMENT "Flashing target hardware (by Texane/STlink) (Remember to reset to run the program)")

		add_custom_target(erase_stflash
			${STFLASH_EXE} erase
			COMMENT "Mass Erase all flash sectors")

		find_program(STUTIL "st-util")
		if (STUTIL)
			add_custom_target(debug_stutil
			${STUTIL} -m -p 3333
			DEPENDS ${PROJECT_NAME}
			COMMENT "Running ST-UTIL as a GDB host (port 3333)")
			set(DEBUG_TARGET debug_stutil PARENT_SCOPE)
		endif()

		set(FLASH_TARGET flash_stflash PARENT_SCOPE)
		set(ERASE_TARGET erase_stflash PARENT_SCOPE)
	endif()
endfunction()

function(cubeprog_targets)
	if (STM32CubeProg)
		add_custom_target(flash_cubeprog
			${STM32CubeProg} -c port=SWD -w ${PROJECT_NAME}.elf -g
			DEPENDS ${PROJECT_NAME}
			COMMENT "Flashing target hardware (by STM32CubeProgrammer)")
		add_custom_target(flash_uart
			${STM32CubeProg} -c port=COM5 -w ${PROJECT_NAME}.elf -g
			DEPENDS ${PROJECT_NAME}
			COMMENT "Flashing target hardware (by UART)")
		add_custom_target(flash_usb
			${STM32CubeProg} -c port=usb0 -w ${PROJECT_NAME}.elf -g
			DEPENDS ${PROJECT_NAME}
			COMMENT "Flashing target hardware (by USB DFU)")
		add_custom_target(erase_cubeprog
			${STM32CubeProg} -c port-SWD -e all
			COMMENT "Mass Erase all flash sectors")
		
		add_custom_target(debug_cubeprog
			echo "Debug server unimplemented for Cube Programmer")
		add_custom_target(gdb_cubeprog
			echo "GDB unimplemented for Cube Programmer")

		set(FLASH_TARGET flash_cubeprog PARENT_SCOPE)
		set(ERASE_TARGET erase_cubeprog PARENT_SCOPE)
		# TODO: GDB Debug Server
	endif()
endfunction()

function(openocd_targets)
	if (OPENOCD_EXE)
		add_custom_target(flash_openocd
		  ${OPENOCD_EXE} ${OPENOCD_CFG} -c "transport select hla_swd"
		  -c "init" -c "reset halt"
		  -c "flash write_image erase ${PROJECT_NAME}.elf" -c "reset run" -c "shutdown"
		  DEPENDS ${PROJECT_NAME}
		  COMMENT "Flashing target hardware (by OpenOCD)")

		add_custom_target(debug_openocd
		  ${OPENOCD_EXE} ${OPENOCD_CFG}
		  DEPENDS ${PROJECT_NAME}
		  COMMENT "Running OpenOCD as a GDB host (port 3333)")

		add_custom_target(gdb_openocd
			gdbgui -g arm-none-eabi-gdb ${PROJECT_NAME}.elf --gdb-args="-x ${GDB_DEBUG_FILE}")

		add_custom_target(erase_openocd
		  ${OPENOCD_EXE} ${OPENOCD_CFG} -c "transport select hla_swd"
		  -c "init" -c "reset halt"
		  -c "flash erase_sector 0 0 last" -c "shutdown"
		  DEPENDS ${PROJECT_NAME}
		  COMMENT "Mass Erase all flash sectors")

		set(FLASH_TARGET flash_openocd PARENT_SCOPE)
		set(ERASE_TARGET erase_openocd PARENT_SCOPE)
		set(DEBUG_TARGET debug_openocd PARENT_SCOPE)
		set(GDB_TARGET gdb_openocd PARENT_SCOPE)
	endif()
endfunction()

function(blackmagic_targets)
    if(NOT WINDOWS)
		add_custom_target(flash_blackmagic
		  arm-none-eabi-gdb ${PROJECT_NAME}.elf 
            -ex 'target extended-remote /dev/cu.usbmodemB5D699FD1'
            -ex 'monitor swdp_scan'
            -ex 'att 1'
            -ex 'load'
            -ex 'compare-sections'
            -ex 'set confirm off'
            -ex 'quit'
            DEPENDS ${PROJECT_NAME}
            COMMENT "Flashing target hardware (by BMP)")
    else()
        add_custom_target(flash_blackmagic
		  arm-none-eabi-gdb ${PROJECT_NAME}.elf 
            -ex 'target extended-remote COM#'
            -ex 'att 1'
            -ex 'load'
            -ex 'compare-sections'
            -ex 'set confirm off'
            -ex 'quit'
            DEPENDS ${PROJECT_NAME}
            COMMENT "Flashing target hardware (by BMP)")
    endif()
    set(FLASH_TARGET flash_blackmagic PARENT_SCOPE)
    #set(ERASE_TARGET erase_blackmagic PARENT_SCOPE)
endfunction()

if(NOT DEFINED DEFAULT_PROGRAMMER)
	stlinkutil_targets()
	stflash_targets()
	openocd_targets()
	cubeprog_targets()	
    blackmagic_targets()
else()
	if(DEFAULT_PROGRAMMER STREQUAL "STM32CUBEPROG")
		stlinkutil_targets()
		stflash_targets()
		openocd_targets()
		cubeprog_targets()	
		blackmagic_targets()
	elseif(DEFAULT_PROGRAMMER STREQUAL "OPENOCD")
		stlinkutil_targets()
		stflash_targets()
		cubeprog_targets()	
		openocd_targets()
		blackmagic_targets()
	elseif(DEFAULT_PROGRAMMER STREQUAL "STFLASH" OR DEFAULT_PROGRAMMER STREQUAL "TEXANE")
		stlinkutil_targets()
		openocd_targets()
		cubeprog_targets()	
		stflash_targets()
		blackmagic_targets()
	elseif(DEFAULT_PROGRAMMER STREQUAL "STLINKUTILITY")
		stflash_targets()
		openocd_targets()
		cubeprog_targets()	
		stlinkutil_targets()
		blackmagic_targets()
	endif()
endif()

if (DEFINED FLASH_TARGET)
	add_custom_target(flash DEPENDS ${FLASH_TARGET})
	message("flash using ${FLASH_TARGET}")
else()
	message("No program found for flash")
endif()
if (DEFINED ERASE_TARGET)
	add_custom_target(erase DEPENDS ${ERASE_TARGET})
	message("erase using ${ERASE_TARGET}")
else()
	message("No program found for erase")
endif()
if (DEFINED DEBUG_TARGET)
	add_custom_target(debug DEPENDS ${DEBUG_TARGET})
	message("debug using ${DEBUG_TARGET}")
else()
	message("No program found for debug")
endif()
if (DEFINED GDB_TARGET)
	add_custom_target(gdb DEPENDS ${GDB_TARGET})
	message("gdb using ${GDB_TARGET}")
else()
	message("No program found for gdb")
endif()

