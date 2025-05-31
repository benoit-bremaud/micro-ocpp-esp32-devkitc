#include <Arduino.h>
#include <unity.h>
#include <SPIFFS.h>

#include "FileLogger.cpp"

// Indique EXPLICITEMENT le chemin correct du Logger.h ET du Logger.cpp
#include "../features/infra/logging/Logger.h"
#include "../src/Logger.cpp" // Inclusion directe obligatoire ici
#include "../features/infra/logging/log_macros.h" // Pour les macros LOG_DEBUG

void test_log_history_overflow() {
    Logger& logger = Logger::getInstance();
    logger.clearHistory(); // réinitialisation avant le test
    logger.setLevel(LOG_LEVEL_DEBUG);

    const size_t N = Logger::LOG_HISTORY_SIZE;
    for (size_t i = 0; i < N + 5; ++i) {
        LOG_DEBUG("Log %d", i);
    }
    TEST_ASSERT_EQUAL(N, logger.getHistoryCount());

    size_t firstIdx = logger.getHistoryHead();
    String realMsg = logger.getHistoryEntry(firstIdx).message;
    TEST_ASSERT_TRUE(realMsg.indexOf("Log 5") != -1);
}

void test_log_level_filtering() {
    Logger& logger = Logger::getInstance();
    logger.clearHistory(); // <-- réinitialisation du buffer avant le test
    logger.setLevel(LOG_LEVEL_INFO);

    LOG_DEBUG("Debug should not be stored");
    LOG_INFO("Info should be stored");

    // Vérifie que l'historique contient exactement un log : "Info should be stored"
    size_t count = logger.getHistoryCount();
    TEST_ASSERT_EQUAL(1, count);

    // Le log stocké doit être exactement "Info should be stored"
    size_t idx = logger.getHistoryHead();
    const LogEntry& entry = logger.getHistoryEntry(idx);
    TEST_ASSERT_TRUE(entry.message.indexOf("Info should be stored") != -1);
}


void test_log_context_integrity() {
    Logger& logger = Logger::getInstance();
    logger.clearHistory(); // réinitialisation avant le test
    logger.setLevel(LOG_LEVEL_DEBUG);

    LOG_DEBUG("Test context integrity");

    // Vérifie que file, function, line sont non vides
    size_t lastIdx = (logger.getHistoryHead() + logger.getHistoryCount() - 1) % Logger::LOG_HISTORY_SIZE;
    const LogEntry& entry = logger.getHistoryEntry(lastIdx);

    TEST_ASSERT_TRUE(entry.file.length() > 0);
    TEST_ASSERT_TRUE(entry.function.length() > 0);
    TEST_ASSERT_TRUE(entry.line > 0);
}

void test_logger_spiffs() {
    TEST_ASSERT_TRUE(SPIFFS.begin(true));
    File f = SPIFFS.open("/unittest.txt", FILE_WRITE);
    TEST_ASSERT_TRUE(f);
    f.println("hello");
    f.close();
    TEST_ASSERT_TRUE(SPIFFS.exists("/unittest.txt"));
}
