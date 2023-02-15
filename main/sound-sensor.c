#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"

#include "gpio_setup.h"
#include "adc_module.h"
#include "pwm.h"

#define MIC GPIO_NUM_21
#define LED1 GPIO_NUM_2

void time_mode(void *params)
{
  pinMode(MIC, GPIO_INPUT);

  int val = 0;
  while (true)
  {
    int sound_signal = digitalRead(MIC);
    sound_signal = sound_signal;
    if (sound_signal == 0)
    {
      val += 50;
      val %= 100;
      pwm_set_value(val);
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}