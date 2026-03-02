#include "firebase_stream.h"
#include "firebase_strm.h"
#include "config.h"
#include "firebase_put.h"
#include "serial.h"
#include "global.h"


// ===================== TIMING =====================
const unsigned long STREAM_TIMEOUT = 30000;

void strm() {
  while (fbStream.connected() && fbStream.available()) {

    String line = fbStream.readStringUntil('\n');
    line.trim();
    if (!line.startsWith("data:")) continue;

    String json = line.substring(5);
    json.trim();
    if (json == "null") continue;

    StaticJsonDocument<512> doc;   // FIX
    if (deserializeJson(doc, json)) continue;

    String path = doc["path"] | "";
    JsonVariant data = doc["data"];

    lastStreamActivity = millis();

    if (path.length() && data.is<bool>()) {
      int relay = path.substring(1).toInt();
      if (relay >= 0 && relay < 12 && !emergencyActive) {
        sendRelay(relay, data.as<bool>());
      }
    }
  }

  if (millis() - lastStreamActivity > STREAM_TIMEOUT) {
    fbStream.stop();           // FIX
    openFirebaseStream();
  }
}

