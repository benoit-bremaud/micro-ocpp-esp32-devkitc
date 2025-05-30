#include <Arduino.h>
#include <unity.h>

// External test function declarations
void test_boot_notification();
void test_system();
void test_log_history_overflow();
void test_log_level_filtering();
void test_log_context_integrity();

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_system);

    RUN_TEST(test_log_history_overflow);
    RUN_TEST(test_log_level_filtering);
    RUN_TEST(test_log_context_integrity);

    RUN_TEST(test_boot_notification);
    UNITY_END();
}   

void loop() {}
