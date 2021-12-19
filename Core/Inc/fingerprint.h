/*
 * fingerprint.h
 *
 *  Created on: Nov 18, 2021
 *      Author: Steven
 */

#ifndef INC_FINGERPRINT_H_
#define INC_FINGERPRINT_H_

#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart1;
#define UART_HANDLER huart1

#define FINGERPRINT_OK 0x00               //!< Command execution is complete
#define FINGERPRINT_PACKETRECIEVEERR 0x01 //!< Error when receiving data package
#define FINGERPRINT_NOFINGER 0x02         //!< No finger on the sensor
#define FINGERPRINT_IMAGEFAIL 0x03        //!< Failed to enroll the finger
#define FINGERPRINT_IMAGEMESS                                                  \
  0x06 //!< Failed to generate character file due to overly disorderly
       //!< fingerprint image
#define FINGERPRINT_FEATUREFAIL                                                \
  0x07 //!< Failed to generate character file due to the lack of character point
       //!< or small fingerprint image
#define FINGERPRINT_NOMATCH 0x08  //!< Finger doesn't match
#define FINGERPRINT_NOTFOUND 0x09 //!< Failed to find matching finger
#define FINGERPRINT_ENROLLMISMATCH                                             \
  0x0A //!< Failed to combine the character files
#define FINGERPRINT_BADLOCATION                                                \
  0x0B //!< Addressed PageID is beyond the finger library
#define FINGERPRINT_DBRANGEFAIL                                                \
  0x0C //!< Error when reading template from library or invalid template
#define FINGERPRINT_UPLOADFEATUREFAIL 0x0D //!< Error when uploading template
#define FINGERPRINT_PACKETRESPONSEFAIL                                         \
  0x0E //!< Module failed to receive the following data packages
#define FINGERPRINT_UPLOADFAIL 0x0F  //!< Error when uploading image
#define FINGERPRINT_DELETEFAIL 0x10  //!< Failed to delete the template
#define FINGERPRINT_DBCLEARFAIL 0x11 //!< Failed to clear finger library
#define FINGERPRINT_PASSFAIL                                                   \
  0x13 //!< Find whether the fingerprint passed or failed
#define FINGERPRINT_INVALIDIMAGE                                               \
  0x15 //!< Failed to generate image because of lac of valid primary image
#define FINGERPRINT_FLASHERR 0x18   //!< Error when writing flash
#define FINGERPRINT_INVALIDREG 0x1A //!< Invalid register number
#define FINGERPRINT_ADDRCODE 0x20   //!< Address code
#define FINGERPRINT_PASSVERIFY 0x21 //!< Verify the fingerprint passed
#define FINGERPRINT_STARTCODE                                                  \
  0xEF01 //!< Fixed falue of EF01H; High byte transferred first

#define FINGERPRINT_COMMANDPACKET 0x1 //!< Command packet
#define FINGERPRINT_DATAPACKET                                                 \
  0x2 //!< Data packet, must follow command packet or acknowledge packet
#define FINGERPRINT_ACKPACKET 0x7     //!< Acknowledge packet
#define FINGERPRINT_ENDDATAPACKET 0x8 //!< End of data packet

#define FINGERPRINT_TIMEOUT 0xFF   //!< Timeout was reached
#define FINGERPRINT_BADPACKET 0xFE //!< Bad packet was sent

#define FINGERPRINT_GETIMAGE 0x01 //!< Collect finger image
#define FINGERPRINT_IMAGE2TZ 0x02 //!< Generate character file from image
#define FINGERPRINT_SEARCH 0x04   //!< Search for fingerprint in slot
#define FINGERPRINT_REGMODEL                                                   \
  0x05 //!< Combine character files and generate template
#define FINGERPRINT_STORE 0x06          //!< Store template
#define FINGERPRINT_LOAD 0x07           //!< Read/load template
#define FINGERPRINT_UPLOAD 0x08         //!< Upload template
#define FINGERPRINT_DELETE 0x0C         //!< Delete templates
#define FINGERPRINT_EMPTY 0x0D          //!< Empty library
#define FINGERPRINT_READSYSPARAM 0x0F   //!< Read system parameters
#define FINGERPRINT_SETPASSWORD 0x12    //!< Sets passwords
#define FINGERPRINT_VERIFYPASSWORD 0x13 //!< Verifies the password
#define FINGERPRINT_HISPEEDSEARCH                                              \
  0x1B //!< Asks the sensor to search for a matching fingerprint template to the
       //!< last model generated
#define FINGERPRINT_TEMPLATECOUNT 0x1D //!< Read finger template numbers
#define FINGERPRINT_AURALEDCONFIG 0x35 //!< Aura LED control
#define FINGERPRINT_LEDON 0x50         //!< Turn on the onboard LED
#define FINGERPRINT_LEDOFF 0x51        //!< Turn off the onboard LED

#define FINGERPRINT_LED_BREATHING 0x01   //!< Breathing light
#define FINGERPRINT_LED_FLASHING 0x02    //!< Flashing light
#define FINGERPRINT_LED_ON 0x03          //!< Always on
#define FINGERPRINT_LED_OFF 0x04         //!< Always off
#define FINGERPRINT_LED_GRADUAL_ON 0x05  //!< Gradually on
#define FINGERPRINT_LED_GRADUAL_OFF 0x06 //!< Gradually off
#define FINGERPRINT_LED_RED 0x01         //!< Red LED
#define FINGERPRINT_LED_BLUE 0x02        //!< Blue LED
#define FINGERPRINT_LED_PURPLE 0x03      //!< Purple LED

//#define FINGERPRINT_DEBUG

#define DEFAULTTIMEOUT 1000 //!< UART reading timeout in milliseconds

// Parameters

// Parameters end

typedef struct{
	  uint16_t start_code; ///< "Wakeup" code for packet detection
	  uint64_t address;  ///< 32-bit Fingerprint sensor address
	  uint8_t type;        ///< Type of packet
	  uint16_t length;     ///< Length of packet
	  uint8_t data[64];    ///< The raw buffer for packet payload
	  uint16_t checksum;
} F_Packet;

void init_fingerprint();
void setup_packet(uint8_t *data, uint8_t size);
void setup_received( uint8_t *data);
void send();
void receive();

uint8_t save_fingerprint(uint8_t id); //max is 64 cuz lazy
uint8_t check_fingerprint(); //return id
void led_mode(uint8_t control);

uint16_t get_template_number();
void reset_database();

#endif /* INC_FINGERPRINT_H_ */
