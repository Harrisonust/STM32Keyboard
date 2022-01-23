#include "hid_queue.h"

uint8_t len(const HID_Queue* q) {
    return q->ptr;
}

uint8_t full(const HID_Queue* q) {
    if (len(q) >= QUEUE_LEN)
        return 1;
    return 0;
}

uint8_t empty(const HID_Queue* q) {
    if (len(q) <= 0)
        return 1;
    return 0;
}

void push(HID_Queue* q, const uint8_t d) {
    if (full(q))
        return;
    q->data[q->ptr] = d;
    q->ptr++;
    return;
}

uint8_t pop(HID_Queue* q) {
    if (empty(q))
        return 0x00;
    const uint8_t d = q->data[q->ptr - 1];
    q->ptr--;
    return d;
}

void clear(HID_Queue* q) {
    for (int i = 0; i < QUEUE_LEN; i++)
        q->data[i] = 0;
    q->ptr = 0;
}