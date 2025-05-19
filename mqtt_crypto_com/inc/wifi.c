#include "wifi.h"

void connect_wifi(const char *ssid, const char *password) 
{
    if (cyw43_arch_init()) {
        printf("Erro ao inicializar Wi-Fi.\n");
        return;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 1000)) {
        printf("Erro ao conectar.\n");
        return;
    }
    
    printf("Conectado a %s.\n", ssid);
}