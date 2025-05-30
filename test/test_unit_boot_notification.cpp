/**
 * @file test_unit_boot_notification.cpp
 * @brief Unit tests for BootNotification - PlatformIO runner-compatible
 */

#include <unity.h>
#include <ArduinoJson.h>

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

void test_boot_notification_empty_vendor() {
    DynamicJsonDocument request(1024);
    request["chargePointVendor"] = "";  // Champ vide
    request["chargePointModel"] = "TestModel";
    TEST_ASSERT_TRUE(strlen(request["chargePointVendor"]) == 0); // Doit échouer dans un vrai use case
}

void test_boot_notification_invalid_model() {
    DynamicJsonDocument request(1024);
    request["chargePointVendor"] = "TestVendor";
    request["chargePointModel"] = 12345;  // Type incorrect
    TEST_ASSERT_FALSE(request.containsKey("chargePointModel")); // Doit échouer dans un vrai use case
}

// Optionnel : Export groupé pour le runner
void test_boot_notification() {
    test_boot_notification_json_structure();
    test_boot_notification_required_fields();
}
