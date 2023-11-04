#ifndef WIFI_H
#define WIFI_H


//static void event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);


//static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

void wifi_init_sta(void);

void wifi_connection(void);


#endif