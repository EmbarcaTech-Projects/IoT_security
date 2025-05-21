#ifndef MQTT_H
#define MQTT_H

#include "lwip/apps/mqtt.h"
#include "lwipopts.h"

#define BROKER_PORT 1883
#define CLIENT_ID "pico_client"
#define BROKER_IP "192.168.1.113"
#define MQTT_USER "user1"
#define MQTT_PASS "trt567"

void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass);
void mqtt_conn_publish(const char *topic, const char *message, size_t message_len, uint8_t qos, uint8_t retain);
#endif