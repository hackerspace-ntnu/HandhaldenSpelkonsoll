#ifndef COMMS_H
#define COMMS_H

#include <esp_now.h>
#include <esp_wifi.h>
#include <stdio.h>

void print_mac(const uint8_t* mac);
void add_new_peer(const uint8_t* mac);
bool compare_data(const uint8_t* a1, const uint8_t* a2,  int len);


uint8_t dummy_address[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t* my_mac_address;
uint8_t other_mac_address[6];

bool CONNECTION_MADE = false;

#endif
    