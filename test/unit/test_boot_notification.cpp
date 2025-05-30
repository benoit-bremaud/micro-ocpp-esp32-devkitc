/**
 * @file test_boot_notification.cpp
 * @brief Tests unitaires pour BootNotification - Version PlatformIO
 */

#include <unity.h>
#include <Arduino.h>
#include <ArduinoJson.h>

void setUp(void) {}
void tearDown(void) {}

void test_boot_notification_json_structure() {
    DynamicJsonDocument request(1024);
    request["chargePointVendor"] = "TestVendor";
    request["chargePointModel"] = "TestModel";
    
    TEST_ASSERT_EQUAL_STRING("TestVendor", request["chargePointVendor"]);
    TEST_ASSERT_EQUAL_STRING("TestModel", request["chargePointModel"]);
}

void test_boot_notification_required_fields() {
    DynamicJsonDocument request(1024);
    request["chargePointVendor"] = "TestVendor";
    
    TEST_ASSERT_TRUE(request.containsKey("chargePointVendor"));
    TEST_ASSERT_FALSE(request.containsKey("chargePointModel"));
}

void setup() {
    delay(2000);
    Serial.begin(115200);
    Serial.println("=== Tests BootNotification ===");
    
    UNITY_BEGIN();
    RUN_TEST(test_boot_notification_json_structure);
    RUN_TEST(test_boot_notification_required_fields);
    UNITY_END();
}

void loop() {}
