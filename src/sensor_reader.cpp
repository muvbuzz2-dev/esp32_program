#include <Arduino.h>
#include "sensor_reader.h"
#include "mqtt_manager.h"

#define SENSOR_PIN 34

unsigned long lastRead = 0;

void sensor_init() {
    pinMode(SENSOR_PIN, INPUT);
}

void sensor_task() {
    if (millis() - lastRead > 5000) {
        lastRead = millis();
        int value = analogRead(SENSOR_PIN);

        char buffer[20];
        sprintf(buffer, "%d", value);

        mqtt_publish("device/sensor", buffer);
    }
}
