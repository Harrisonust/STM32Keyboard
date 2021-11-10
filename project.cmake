# Set the variable and resource directories for the current project
# 
# 
# Remember to use PARENT_SCOPE or it is useless
#

##############################################################################################################################################################################
function(user_proj_config)
	set(PROJ_NAME "Elec3300Keyboard" PARENT_SCOPE)

	set(STM32FXXX "STM32F103VE" PARENT_SCOPE)
	set(USE_GCC 1 PARENT_SCOPE)                #use gcc instead of armcc
	# set(STFU_GCC 1 PARENT_SCOPE)               #tell gcc to shut the fuck up because it has so many more warnings
	set(CUBE_PROJECT 1 PARENT_SCOPE)           #This is a cube generated project (DCUBE_PROJECT_LL means use LL)
	# set(CMAKE_BUILD_TYPE Release PARENT_SCOPE) #Debug doesn't optimize so compiles faster and runs slower
	# set(USING_FREERTOS 0 PARENT_SCOPE)         #disable FreeRTOS
	# set(ARMCC_GNU_COMPAT 1 PARENT_SCOPE)       #add --gnu option to the armcc
	# set(ARMCC_MICROLIB 1 PARENT_SCOPE)         #tells arm to use the MicroLIB instead of std libc, broken for some reason
	set(USE_LTO 1 PARENT_SCOPE)
	# set(XTAL)
	# set(CMAKE_VERBOSE_MAKEFILE)

	# User Configuration 
	# - If your project is a special snowflake you can customize some stuff here, most defaults are good tho

	# C DEFINES
	# set(USER_DEFINES -DSTM32F10X_MD)

	# Source Files - Any C file anywhere inside the src/ folder will be compiled and linked
	# file(GLOB_RECURSE SOURCE_FILES "./src/*.c")

	# Include Directories - Compiler searches here for included header files 
	# file(GLOB INCLUDE_DIRS "./src/*/") # Any directory in src
	# set(INCLUDE_DIRS ${INCLUDE_DIRS} ./RTE/_${STM32FXXX}) # Keil-specific garbage

	# Statically Linked Libraries
	# file(GLOB LINK_LIBRARIES "./lib/${USE_COMPILER}/*")

	# Scatter File - Used by linker to layout memory
	# get_filename_component(SCATTER_FILE ./STM32F429_439xx/STM32F429_439xx.sct ABSOLUTE)

	# set(MCU_STARTUP_DIR "./src/startup") # Will go in to compiler specific directory and then find MCU specific startup file
	# set(MCU_STARTUP_FILENAME startup_stm32f103xb.s)
	# set(MCU_STARTUP_FILE) # Directly use this as the startup filename
endfunction(user_proj_config)
##############################################################################################################################################################################
