#include "mqtt.h"

static mqtt_client_t *client;

/**
 * Função de callback para quando a conexão MQTT é estabelecida.
 *
 * @param client Ponteiro para o cliente MQTT.
 * @param arg Argumento adicional (não utilizado).
 * @param status Status da conexão.
 */
static void mqtt_connection_callback(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
        printf("Conectado ao broker MQTT.\n");
    else
        printf("Falha ao conectar ao broker: %d\n", status);
}

/**
 * Função para configurar o cliente MQTT.
 *
 * @param client_id ID do cliente MQTT.
 * @param broker_ip IP do broker MQTT.
 * @param user Nome de usuário (opcional).
 * @param pass Senha (opcional).
 */
void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass)
{
    ip_addr_t broker_addr;

    if (!ipaddr_aton(broker_ip, &broker_addr))
    {
        printf("Erro no IP.\n");
        return;
    }

    client = mqtt_client_new();
    if (!client)
    {
        printf("Falha ao criar cliente.\n");
        return;
    }

    struct mqtt_connect_client_info_t ci = {
        .client_id = client_id,
        .client_user = user,
        .client_pass = pass};

    mqtt_client_connect(client, &broker_addr, BROKER_PORT, mqtt_connection_callback, NULL, &ci);
}

/**
 * Callback de confirmação de publicação.
 * 
 * @param arg Argumento adicional (não utilizado).
 * @param result Resultado da publicação.
 */
static void mqtt_pub_request_callback(void *arg, err_t result) 
{
    if (result == ERR_OK) {
        printf("Mensagem publicada com sucesso.\n");
    } else {
        printf("Falha ao publicar mensagem: %d\n", result);
    }
}

/**
 * Função para publicar uma mensagem no tópico MQTT.
 *
 * @param topic Tópico onde a mensagem será publicada.
 * @param message Mensagem a ser publicada.
 * @param message_len Tamanho da mensagem.
 */
void mqtt_conn_publish(const char *topic, const char *message, size_t message_len, uint8_t qos, uint8_t retain)
{
    err_t response = mqtt_publish(
        client,
        topic,
        message,
        message_len,
        qos, // QoS
        retain, // Retain
        mqtt_pub_request_callback,
        NULL
    );

    if (response != ERR_OK) {
        printf("Erro ao publicar mensagem: %d\n", response);
    }
}