#include <Arduino.h>
#include <WiFi.h>
#include <MicroOcpp.h>
#include "config.h"

void connectToWiFi() {
  Serial.print("[Wi-Fi] Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  uint8_t retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi connected");
    Serial.print("📡 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to Wi-Fi");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("[BOOT] Starting ESP32...");
  connectToWiFi();

  // -- API Arduino MicroOcpp --
  mocpp_initialize(OCPP_ENDPOINT, CHARGE_BOX_ID);
}

void loop() {
  mocpp_loop();
}
