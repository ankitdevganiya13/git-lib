#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
//#include "nvs_flash.h"
#include "esp_netif.h"

#include "lwip/sockets.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "mqtt_client.h"

#include <inttypes.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "wifi.h"

// #include "https.h"

#include "mqtt.h"

#include "NVS_FL.h"

#include "SPIFFS.h"


#include "cJSON.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_wifi.h"
#include "update.h"



// Blink task
void blink_task(void *pvParameter) {
	
    esp_rom_gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}




// void app_main(void)
// {
//     NVS_INIT();

//     vTaskDelay(2000 / portTICK_PERIOD_MS);

//     NVS_read_function();
//     NVS_write_function("JAY SWAMINARAYAN\n");

//     SPIFFS_INIT();

//     SPIFFS_Read("data.txt");

//     wifi_connection();

//     vTaskDelay(2000 / portTICK_PERIOD_MS);
//     printf("WIFI was initiated ...........\n\n");

//     mqtt_app_start("testing ESP32 DEVICE","my_topic");


// ////////////////////////////////////////
//     // printf("Firmware 1\n");

//     // int a = check_updates();
//     // if(a==1){
//     //     update();
//     // }
//     // printf("Firmware 1\n");

    
// }


void app_main() {

    NVS_INIT();

    vTaskDelay(2000 / portTICK_PERIOD_MS);
	
	//printf("HTTPS OTA, firmware %.1f\n\n", FIRMWARE_VERSION);
	
	// start the blink task
	//xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
	
	// connect to the wifi network
    wifi_connection();

    vTaskDelay(2000 / portTICK_PERIOD_MS);
    printf("WIFI was initiated ...........\n\n");
	
	
    check_update_task();
	
}
