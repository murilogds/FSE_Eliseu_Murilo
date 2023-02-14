#ifndef SENSOR_H_
#define SENSOR_H_
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "gpio_setup.h"
#include "adc_module.h"

void switch_mode();
void time_mode();

#endif