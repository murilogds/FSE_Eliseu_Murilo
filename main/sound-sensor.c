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

  int time = 0;
  while (true)
  {
    int sound_signal = digitalRead(MIC);
    sound_signal = sound_signal;
    if (sound_signal == 0)
    {
      pwm_set_value((pwm_get_value() + 50)%100);
      // time = 0;
    }

    // time++;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}