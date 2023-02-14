#ifndef MQTT_H
#define MQTT_H

#include "cJSON.h"
#include "mqtt_client.h"

void mqtt_start();

void mqtt_envia_mensagem(char * topico, char * mensagem);

void readRPC(esp_mqtt_event_handle_t event);

#endif