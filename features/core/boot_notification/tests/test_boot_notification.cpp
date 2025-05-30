#include <unity.h>
#include "../boot_notification_handler.h"

BootNotificationHandler handler;

void test_create_request_with_required_fields() {
    BootNotificationHandler::BootNotificationData data;
    data.chargePointVendor = "TestVendor";
    data.chargePointModel = "TestModel";
    
    auto request = handler.createRequest(data);
    
    TEST_ASSERT_EQUAL_STRING("TestVendor", request["chargePointVendor"]);
    TEST_ASSERT_EQUAL_STRING("TestModel", request["chargePointModel"]);
}

void test_validate_request_missing_required_field() {
    DynamicJsonDocument request(256);
    request["chargePointVendor"] = "TestVendor";
    // chargePointModel manquant
    
    TEST_ASSERT_FALSE(handler.validateRequest(request));
}

void test_validate_request_string_too_long() {
    DynamicJsonDocument request(256);
    request["chargePointVendor"] = "ThisStringIsWayTooLongForTheSpecification";
    request["chargePointModel"] = "TestModel";
    
    TEST_ASSERT_FALSE(handler.validateRequest(request));
}

void test_parse_response_accepted() {
    DynamicJsonDocument response(256);
    response["status"] = "Accepted";
    response["currentTime"] = "2024-01-01T12:00:00Z";
    response["interval"] = 300;
    
    auto parsed = handler.parseResponse(response);
    
    TEST_ASSERT_EQUAL(BootNotificationHandler::BootNotificationStatus::ACCEPTED, parsed.status);
    TEST_ASSERT_EQUAL_STRING("2024-01-01T12:00:00Z", parsed.currentTime.c_str());
    TEST_ASSERT_EQUAL(300, parsed.interval);
}

void setup() {
    UNITY_BEGIN();
    
    RUN_TEST(test_create_request_with_required_fields);
    RUN_TEST(test_validate_request_missing_required_field);
    RUN_TEST(test_validate_request_string_too_long);
    RUN_TEST(test_parse_response_accepted);
    
    UNITY_END();
}

void loop() {
    // Tests unitaires exécutés une seule fois
}
