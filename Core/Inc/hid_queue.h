#ifndef HID_QUEUE_H
#define HID_QUEUE_H

#include "main.h"

#define QUEUE_LEN 6
typedef struct {
    uint8_t data[QUEUE_LEN];
    uint8_t ptr;
} HID_Queue;

uint8_t len(const HID_Queue* q);

uint8_t full(const HID_Queue* q);

uint8_t empty(const HID_Queue* q);

void push(HID_Queue* q, const uint8_t d);

uint8_t pop(HID_Queue* q);

void clear(HID_Queue* q);

#endif