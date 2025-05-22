#include <stdio.h>
#include "pico/stdlib.h"
#include "lwipopts.h"
#include "inc/wifi.h"
#include "inc/mqtt.h"

#define G_LED 11
#define R_LED 13

int main()
{
    stdio_init_all();

    // LEDs
    gpio_init(R_LED);
    gpio_set_dir(R_LED, GPIO_OUT);
    gpio_init(G_LED);
    gpio_set_dir(G_LED, GPIO_OUT);

    sleep_ms(3000); 

    int r = connect_wifi(WIFI_SSID, WIFI_PASSWORD);
    sleep_ms(500);

    if (r > 0) {
        gpio_put(G_LED, 1);
        sleep_ms(1000);
        gpio_put(G_LED, 0);
        mqtt_setup(CLIENT_ID, BROKER_IP, MQTT_USER, MQTT_PASS);
    } else {
        gpio_put(R_LED, 1);
        sleep_ms(1000);
        gpio_put(R_LED, 0);
    }

    sleep_ms(1000);

    const char *message = "Hello, MQTT com criptografia xor!";
    
    uint8_t enc_message[256];
    xor_encrypt_message((uint8_t *)message, enc_message, strlen(message), 42);
    mqtt_conn_publish("test/topic/xor", enc_message, strlen(enc_message), 0, 0);

    const uint8_t key[16] = "minha_chave_1234";
    memset(enc_message, 0, sizeof(enc_message));
    size_t enc_len = aes_encrypt_message((uint8_t *)message, enc_message, strlen(message), key);
    mqtt_conn_publish("test/topic/aes", enc_message, enc_len, 0, 0);

    while (true) {
    
    }
}
