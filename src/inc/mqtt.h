#ifndef MQTT_H
#define MQTT_H

#include "lwip/apps/mqtt.h"
#include "lwipopts.h"

#define BROKER_PORT 1883
#define CLIENT_ID "pico_client"
#define BROKER_IP "192.168.1.113"
#define MQTT_USER NULL
#define MQTT_PASS NULL

void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass);

#endif