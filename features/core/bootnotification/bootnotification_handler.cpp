#include "bootnotification_handler.h"
#include <MicroOcpp.h>
#include <ArduinoJson.h>
#include <Arduino.h>

// Callback for BootNotification.conf
void onBootNotificationConf(JsonObject response) {
    const char* status = response["status"];
    const char* currentTime = response["currentTime"];
    int interval = response["interval"];

    Serial.printf("[BootNotification.conf] Status: %s | Time: %s | HeartbeatInterval: %d\n",
                  status, currentTime, interval);

    // TODO: Add business logic here based on status, e.g.:
    // if (strcmp(status, "Accepted") == 0) { ... }
    // else if (strcmp(status, "Rejected") == 0) { ... }
}
void setupBootNotification() {

}
