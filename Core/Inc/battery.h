#ifndef BATTERY_H
#define BATTERY_H

// TODO: need to find out these value
#define MAX_BATT 2048
#define MIN_BATT 1639

void battery_handler();

void battery_display_update();

#endif