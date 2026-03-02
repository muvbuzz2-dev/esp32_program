#include "serial.h"
#include "config.h"


void sendRelay(uint8_t relay, bool state) {

  Wire.beginTransmission(RELAY_SLAVE_ADDR);
  Wire.write(relay);
  Wire.write(state ? 1 : 0);
  Wire.endTransmission();

  Serial.printf("Relay %d → %s\n", relay, state ? "ON" : "OFF");
}
