#include <Arduino.h>
#include <unity.h>

// External test function declarations
void test_boot_notification();
void test_system();

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_boot_notification);
    RUN_TEST(test_system);
    UNITY_END();
}

void loop() {}
