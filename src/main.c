#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/wifi.h"
#include "lwipopts.h"


int main()
{
    stdio_init_all();

    connect_wifi(WIFI_SSID, WIFI_PASSWORD);
    sleep_ms(500);
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
