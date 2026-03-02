#ifndef config
#define config


// WiFi
#define WIFI_SSID     "Airtel_tanm_1065"
#define WIFI_PASS     "air75660"

// Device / Cloud
#define DEVICE_ID     "ESP32_001"
#define FIREBASE_HOST "drip-irrigation-01-default-rtdb.asia-southeast1.firebasedatabase.app"

// I2C
#define I2C_SDA 21
#define I2C_SCL 22
#define RELAY_SLAVE_ADDR 0x08

// HX711 pins
#define HX_SCK     25
#define HX1_DOUT  32
#define HX2_DOUT  33
#define HX3_DOUT  34
#define HX4_DOUT  35

// HX settings
#define HX_DIVIDER        5.0
#define TANK_MAX_WEIGHT  5000.0

// Emergency
#define EMERGENCY_BTN 26

extern unsigned long lastStreamActivity;


#endif

