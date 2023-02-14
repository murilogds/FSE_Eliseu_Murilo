#ifndef MQTT_H
#define MQTT_H

#include "cJSON.h"

void mqtt_start();

void mqtt_envia_mensagem(char * topico, char * mensagem);

void readRPC(char *data);

#endif