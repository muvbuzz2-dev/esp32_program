#ifndef firebase_put
#define firebase_put

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

extern WiFiClientSecure fbHttp;     // ONLY PUT uploads

void firebasePUT(String path, String payload);

#endif 
