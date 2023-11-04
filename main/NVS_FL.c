#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "NVS_FL.h"


void NVS_INIT(void)
{

    // Initialize NVS
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );


}
    

void NVS_read_function(void){

    esp_err_t err;
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    
    nvs_handle_t my_handle;

    err = nvs_open("storage", NVS_READWRITE, &my_handle);

        if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        printf("Done\n");

    printf("Reading from NVS ... ");

    size_t required_size = 0;

   err = nvs_get_str(my_handle, "data", NULL, &required_size);


        switch (err) {
            case ESP_OK:
                printf("Done\n");

            char *server_name = malloc(required_size);
            nvs_get_str(my_handle, "data", (char *) server_name, &required_size);
            printf("Read data: %s \n", server_name);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The value is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
    
    nvs_close(my_handle);

}
}


void NVS_write_function(char *Server_string){

    esp_err_t err;

    printf("Writing in NVS ... ");
    nvs_handle_t my_handle;

    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    

    //char *write_string = "Hi I Am Ankit Devganiya\0";
 

    err = nvs_set_str(my_handle, "data", Server_string);

    printf("Write data: %s \n", Server_string);
    printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

    printf("Committing updates in NVS ... ");
    nvs_commit(my_handle);
    nvs_close(my_handle);

}
