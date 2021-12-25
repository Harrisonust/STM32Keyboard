/*
 * fingerprint.c
 *
 *  Created on: Nov 18, 2021
 *      Author: Steven
 */

#include "fingerprint.h"

F_Packet fpacket = {
    .start_code = FINGERPRINT_STARTCODE,
    .address = 0xFFFFFFFF,
    .type = FINGERPRINT_COMMANDPACKET,
};

F_Packet rpacket;

uint16_t status_reg = 0x0;    ///< The status register (set by getParameters)
uint16_t system_id = 0x0;     ///< The system identifier (set by getParameters)
uint16_t capacity = 64;       ///< The fingerprint capacity (set by getParameters)
uint16_t security_level = 0;  ///< The security level (set by getParameters)
uint32_t device_addr =
    0xFFFFFFFF;              ///< The device address (set by getParameters)
uint16_t packet_len = 64;    ///< The max packet length (set by getParameters)
uint16_t baud_rate = 57600;  ///< The UART baud rate (set by getParameters)

void init_fingerprint() {
    uint8_t temp = FINGERPRINT_READSYSPARAM;
    setup_packet(&temp, 1);
    receive();
    // insert init;
}

void setup_packet(uint8_t *data, uint8_t size) {
    // setup the length, datasize, and checksum
    if (size > 64)
        return;

    // length
    uint16_t packet_length = 2 + size;
    fpacket.length = size;  // packet size

    // data and checksum
    uint16_t sum =
        ((packet_length) >> 8) + ((packet_length)&0xFF) + fpacket.type;

    for (int i = 0; i < size; i++) {
        fpacket.data[i] = data[0];
        sum += *data;
        data++;
    }
    fpacket.checksum = sum;
    //
}

void setup_received(uint8_t *data) {
    // Data format
    /*
     * 2 bytes of header
     * 4 bytes of address
     * 1 byte of package identifier (type)
     * 2 byte of length
     * n amount of data
     * 2 checksum (which technically u dunnit)
     *
     * */
    rpacket.start_code = ((uint16_t)data[0] << 8) + ((uint16_t)data[1]);
    rpacket.address = ((uint32_t)data[2] << 24) + ((uint32_t)data[3] << 16) +
                      ((uint32_t)data[4] << 8) + ((uint32_t)data[5]);
    rpacket.type = data[6];
    rpacket.length = ((uint16_t)data[7] << 8) + ((uint16_t)data[8]);

    // get all the data
    for (int i = 0; i < rpacket.length - 2; i++) {
        rpacket.data[i] = data[9 + i];
    }
}

void send() {
    // first, send start command
    uint8_t value;

    for (int i = 0; i < 2; i++) {
        value = (fpacket.start_code >> (8 * (1 - i)));
        HAL_UART_Transmit(&UART_HANDLER, &value, 1, 100);
    }

    // second, send chip addr
    for (int i = 0; i < 4; i++) {
        value = 0xFF;
        HAL_UART_Transmit(&UART_HANDLER, &value, 1, 100);
    }

    // third, send package identifier
    value = fpacket.type;
    HAL_UART_Transmit(&UART_HANDLER, &value, 1, 100);

    // fourth, send package length
    uint16_t packet_length = fpacket.length + 2;
    for (int i = 0; i < 2; i++) {
        value = (packet_length >> (8 * (1 - i)));
        HAL_UART_Transmit(&UART_HANDLER, &value, 1, 100);
    }

    // fifth, send package data
    for (int i = 0; i < fpacket.length; i++) {
        value = fpacket.data[i];
        HAL_UART_Transmit(&UART_HANDLER, &value, 1, 100);
    }

    // lastly checksum
    for (int i = 0; i < 2; i++) {
        value = (fpacket.checksum >> (8 * (1 - i)));
        HAL_UART_Transmit(&UART_HANDLER, &value, 1, 100);
    }
}

void receive() {
    uint8_t testing[100] = {0};
    send(fpacket);
    HAL_UART_Receive(&UART_HANDLER, testing, 100,
                     1000);  // logically hitting all the 9 data
    setup_received(testing);

    //	//get data and checksum
    //	HAL_UART_Receive(&UART_HANDLER, &(rpacket->data), rpacket->length - 2 ,
    // timeout);

    //	//set received checksum
    //	rpacket->checksum = rpacke
}

uint8_t save_fingerprint(uint8_t id) {
    uint8_t temp;
    // 1. GetImage
    temp = FINGERPRINT_GETIMAGE;
    setup_packet(&temp, 1);
    receive();

    if (rpacket.data[0])
        return rpacket.data[0];

    // 2. Conv image to value image2Tz
    uint8_t data[4] = {FINGERPRINT_IMAGE2TZ, 1};
    setup_packet(data, 2);
    receive();

    if (rpacket.data[0])
        return rpacket.data[0];

    // 3. GetImage
    setup_packet(&temp, 1);
    receive();

    if (rpacket.data[0])
        return rpacket.data[0];

    // 4. Conv image to value image2Tz
    data[1] = 2;
    setup_packet(data, 2);
    receive(fpacket, rpacket);

    if (rpacket.data[0])
        return rpacket.data[0];

    // 5. Create the model
    temp = FINGERPRINT_REGMODEL;
    setup_packet(&temp, 1);
    receive();
    if (rpacket.data[0])
        return rpacket.data[0];

    for (int i = 4; i < 5; i++) {
        data[0] = FINGERPRINT_STORE;
        data[1] = 0x01;
        data[2] = 0x00;
        data[3] = (uint8_t)(i & 0xFF);
        setup_packet(data, 4);
        receive();
    }
    return rpacket.data[0];
}

uint8_t check_fingerprint() {
    uint8_t temp;
    // 1. GetImage
    temp = FINGERPRINT_GETIMAGE;
    setup_packet(&temp, 1);
    receive();

    if (rpacket.data[0])
        return -3;

    // 2. Conv image to value image2Tz
    uint8_t data[5] = {FINGERPRINT_IMAGE2TZ, 2};
    setup_packet(data, 2);
    receive();

    if (rpacket.data[0])
        return -3;

    // 3. Search for it
    data[0] = FINGERPRINT_SEARCH;
    data[1] = 2;
    data[2] = data[3] = 0x00;
    data[4] = (uint8_t)(capacity << 8);
    data[5] = (uint8_t)(capacity & 0xFF);
    setup_packet(data, 6);
    receive();

    if (rpacket.data[0] == 9) {  // dont exist
        return -1;
    } else if (rpacket.data[0] == 1) {  // error packet
        return -2;
    } else {
        return rpacket.data[0];
    }
}

void led_mode(uint8_t control) {
    if ((control == 0) | (control == 1)) {
        uint8_t temp = control == 0 ? FINGERPRINT_LEDOFF : FINGERPRINT_LEDON;
        setup_packet(&temp, 1);
        receive();
    }
}

uint16_t get_template_number() {
    uint8_t temp;
    temp = FINGERPRINT_TEMPLATECOUNT;
    setup_packet(&temp, 1);
    receive();
    return (((uint16_t)rpacket.data[1]) << 8) + ((uint16_t)rpacket.data[2]);
}

void reset_database() {
    uint8_t temp;
    // 1. GetImage
    temp = FINGERPRINT_EMPTY;
    setup_packet(&temp, 1);
    send();
}
