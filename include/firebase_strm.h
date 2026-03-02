#ifndef firebase_strm
#define firebase_strm

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>

extern WiFiClientSecure fbStream;   // ONLY Firebase stream

bool openFirebaseStream();

#endif
