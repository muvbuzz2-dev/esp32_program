#ifndef serial
#define serial

#include <Arduino.h>  
#include <Wire.h>

void sendRelay(uint8_t relay, bool state);

#endif

