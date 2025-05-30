/**
 * @file test_integration_system.cpp
 * @brief System integration tests - PlatformIO runner-compatible
 */

#include <unity.h>
#include <Arduino.h>

void test_esp32_basic_functions() {
    TEST_ASSERT_GREATER_THAN(0, ESP.getFreeHeap());
    TEST_ASSERT_GREATER_THAN(0, ESP.getFlashChipSize());
}

// Export composite function for runner
void test_system() {
    test_esp32_basic_functions();
}
