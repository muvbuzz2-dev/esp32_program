#include "system_loop.h"
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "valve_engine.h"
#include "sensor_reader.h"
#include "safety_monitor.h"

void system_init() {
    wifi_init();
    mqtt_init();
    valve_engine_init();
    sensor_init();
    safety_init();
}

void system_run() {
    wifi_task();
    mqtt_task();
    sensor_task();
    valve_engine_task();
    safety_task();
}
