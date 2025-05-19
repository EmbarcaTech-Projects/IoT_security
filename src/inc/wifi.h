#ifndef WIFI_H
#define WIFI_H

#include <stdio.h>
#include "pico/cyw43_arch.h"

#define WIFI_SSID "teste" 
#define WIFI_PASSWORD "teste"

void connect_wifi(const char *ssid, const char *password);

#endif