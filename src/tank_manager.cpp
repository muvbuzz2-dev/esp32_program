#include "tank_manager.h"
#include "firebase_put.h"
#include "HX711.h"   
#include "config.h"
#include <Arduino.h>

extern HX711 scale[];

// ===================== HX711 =====================
float readHX(uint8_t idx) {
  return scale[idx].get_units(5);
}

// ===================== TANK UPLOAD =====================
void uploadTankData(uint8_t i) {

  float raw = readHX(i) / HX_DIVIDER;  // FIX: read once
  float weight = raw;

  bool filled = weight > 0.5;

  int percentage = constrain(
    (raw) , 0, 100);   // FIX

  String path = "/devices/" + String(DEVICE_ID) +
                "/tanks/" + String(i) + ".json";

  String payload =
    "{\"weight_g\":" + String(weight, 1) +
    ",\"filled\":" + (filled ? "true" : "false") +
    ",\"percentage\":" + String(percentage) + "}";

  firebasePUT(path, payload);
  Serial.println("Tank " + String(i) + " uploaded");
}

