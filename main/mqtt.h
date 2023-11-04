#ifndef MQTT_H
#define MQTT_H


//static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event);

//static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

void mqtt_app_start(char *pub_msg,char *topic);

#endif