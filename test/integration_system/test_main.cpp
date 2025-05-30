// test/integration_system/test_main.cpp
// Tests d'intégration système pour PlatformIO
#include <unity.h>
#include <Arduino.h>

void setUp(void) {}
void tearDown(void) {}

void test_esp32_basic_functions() {
    TEST_ASSERT_GREATER_THAN(0, ESP.getFreeHeap());
    TEST_ASSERT_GREATER_THAN(0, ESP.getFlashChipSize());
}

void setup() {
    delay(2000);
    Serial.begin(115200);
    Serial.println("=== Tests d'Intégration Système ===");
    UNITY_BEGIN();
    RUN_TEST(test_esp32_basic_functions);
    UNITY_END();
}

void loop() {}
