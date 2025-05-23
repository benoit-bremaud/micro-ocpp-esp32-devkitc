#include <WiFi.h>

const char* ssid = "TON_SSID";
const char* password = "TON_MOT_DE_PASSE";

void connectToWiFi() {
  Serial.print("[Wi-Fi] Connecting to ");
  Serial.print(ssid);
  Serial.println("...");

  WiFi.begin(ssid, password);

  uint8_t retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi connected");
    Serial.print("📡 IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to Wi-Fi");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectToWiFi();
}

void loop() {
  // Nothing yet
}
