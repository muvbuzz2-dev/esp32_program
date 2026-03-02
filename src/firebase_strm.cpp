#include "firebase_strm.h"
#include "config.h"



bool openFirebaseStream() {
  fbStream.stop();               // FIX: close old stream
  fbStream.setInsecure();

  if (!fbStream.connect(FIREBASE_HOST, 443)) {
    Serial.println("Firebase stream connect FAILED");
    return false;
  }

  String path = "/devices/" + String(DEVICE_ID) +
                "/relays.json?print=silent";   // FIX

  fbStream.print(
    "GET " + path + " HTTP/1.1\r\n" +
    "Host: " + FIREBASE_HOST + "\r\n" +
    "Accept: text/event-stream\r\n" +
    "Connection: keep-alive\r\n\r\n"
  );

  lastStreamActivity = millis();
  Serial.println("Firebase stream OPEN");
  return true;
}
