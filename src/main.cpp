#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "HX711.h"
#include "serial.h"
#include "connectWiFi.h"
#include "config.h"
#include "global.h"
#include "firebase_stream.h"
#include "firebase_put.h"
#include "firebase_strm.h"
#include "tank_manager.h"

// ===================== OBJECTS =====================
WiFiClientSecure fbStream;   // ONLY Firebase stream
WiFiClientSecure fbHttp;     // ONLY PUT uploads

HX711 scale[4];

// ===================== STATE =====================
unsigned long lastTankUpload = 0;
unsigned long lastEmergencyTime = 0;

// ===================== TIMING =====================
const unsigned long TANK_UPLOAD_INTERVAL = 60000;
const unsigned long EMERGENCY_RESET_TIME = 10000;
const unsigned long BTN_DEBOUNCE = 50;





// ===================== EMERGENCY =====================
void triggerEmergency() {
  emergencyActive = true;
  lastEmergencyTime = millis();

  for (uint8_t i = 0; i < 12; i++) {
    Wire.beginTransmission(RELAY_SLAVE_ADDR);
    Wire.write(i);
    Wire.write(0);
    Wire.endTransmission();
  }

  firebasePUT("/devices/" + String(DEVICE_ID) + "/emergency.json",
              "{\"state\":true}");

  Serial.println("🚨 EMERGENCY ACTIVATED");
}

void wifi_rec() {
  if (WiFi.status() != WL_CONNECTED) {
    if (connect_WiFi()) {
      openFirebaseStream();   // FIX: only after success
    }
  }
}


void tank_upd() {
  if (millis() - lastTankUpload > TANK_UPLOAD_INTERVAL) {
    lastTankUpload = millis();

    for (uint8_t i = 0; i < 4; i++) {
      int perc = constrain(
        (readHX(i) / HX_DIVIDER / TANK_MAX_WEIGHT) * 100, 0, 100);

      if (perc > 95 || perc > 75 && perc < 80 ||
          perc > 58 && perc < 72 ||
          perc > 40 && perc < 45 ||
          perc > 15 && perc < 20 ||
          perc < 5) {
        uploadTankData(i);
      }
    }
  }
}

void eme_btn() {
  static bool lastState = LOW;
  static unsigned long lastBtnTime = 0;

  bool curr = digitalRead(EMERGENCY_BTN);

  if (curr == HIGH && lastState == LOW &&
      millis() - lastBtnTime > BTN_DEBOUNCE) {

    lastBtnTime = millis();
    if (!emergencyActive) triggerEmergency();
  }

  lastState = curr;
}

void auto_rst() {
  if (emergencyActive &&
      millis() - lastEmergencyTime > EMERGENCY_RESET_TIME) {

    emergencyActive = false;
    firebasePUT("/devices/" + String(DEVICE_ID) + "/emergency.json",
                "{\"state\":false}");

    Serial.println("Emergency reset");
  }
}

// ===================== SETUP =====================
void setup() {
  Serial.begin(115200);

  connect_WiFi();

  Wire.begin(I2C_SDA, I2C_SCL);

  pinMode(EMERGENCY_BTN, INPUT_PULLDOWN);

  scale[0].begin(HX1_DOUT, HX_SCK);
  scale[1].begin(HX2_DOUT, HX_SCK);
  scale[2].begin(HX3_DOUT, HX_SCK);
  scale[3].begin(HX4_DOUT, HX_SCK);

  for (int i = 0; i < 4; i++) {
    scale[i].tare();
    scale[i].set_scale(5053.7);
  }

  openFirebaseStream();
}

// ===================== LOOP =====================
void loop() {
  wifi_rec();
  strm();
  tank_upd();
  eme_btn();
  auto_rst();
}
