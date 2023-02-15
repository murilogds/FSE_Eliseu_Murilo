#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "mqtt.h"
#include "dht11.h"
#include "pwm.h"
#include "sound_sensor.h"

SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

void conectadoWifi(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void trataComunicacaoComServidor(void *params)
{
  char tempMensagem[50];
  char humidMensagem[50];
  if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while (true)
    {
      struct dht11_reading dht_status = DHT11_read();
      float temperatura = dht_status.temperature;
      int humidity = dht_status.humidity;
      if (temperatura > -1 && humidity > -1)
      {
        sprintf(tempMensagem, "{\"temperature\": %f}", temperatura);
        mqtt_envia_mensagem("v1/devices/me/telemetry", tempMensagem);
        sprintf(humidMensagem, "{\"umidade\": %d}", humidity);
        mqtt_envia_mensagem("v1/devices/me/attributes", humidMensagem);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
      }
      else
      {
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
    }
  }
}

void app_main(void)
{
  DHT11_init(GPIO_NUM_5);
  // Inicializa o NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();

  wifi_start();
  start_pwm();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
  xTaskCreate(&time_mode, "Sensor de Som", 4096, NULL, 1, NULL);
}
