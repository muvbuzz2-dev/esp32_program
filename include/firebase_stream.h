#ifndef firebase_stream
#define firebase_stream

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <ArduinoJson.h>

extern WiFiClientSecure fbStream;
extern WiFiClientSecure fbHttp;

void strm();

#endif
