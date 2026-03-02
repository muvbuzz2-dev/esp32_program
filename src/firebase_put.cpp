#include "firebase_put.h"
#include "config.h"
 

void firebasePUT(String path, String payload) {
  fbHttp.stop();
  fbHttp.setInsecure();

  if (!fbHttp.connect(FIREBASE_HOST, 443)) {
    Serial.println("Firebase PUT connect failed");
    return;
  }

  fbHttp.print(
    "PUT " + path + " HTTP/1.1\r\n" +
    "Host: " + FIREBASE_HOST + "\r\n" +
    "Content-Type: application/json\r\n" +
    "Content-Length: " + payload.length() + "\r\n\r\n" +
    payload
  );

  // FIX: read response header
  while (fbHttp.connected()) {
    String line = fbHttp.readStringUntil('\n');
    if (line == "\r") break;
  }

  fbHttp.stop();
}

