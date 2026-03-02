#include <WiFi.h>
#include "wifi_manager.h"

const char* ssid = "POCO X5 Pro 5G";
const char* password = "";

void wifi_init() {

    WiFi.begin(ssid);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void wifi_task() {

    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();
    }
}
