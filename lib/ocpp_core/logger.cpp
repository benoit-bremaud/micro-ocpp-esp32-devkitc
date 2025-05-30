#include "logger.h"

log_level_t Logger::currentLevel = LOG_LEVEL;

void Logger::init() {
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial) {
        delay(10);
    }
    
    Serial.println();
    Serial.println("=================================");
    Serial.println("    OCPP Logger Initialized");
    Serial.println("=================================");
    
    LOG_INFO("LOGGER", "Logger initialized - Level: %s", getLevelString(currentLevel));
    LOG_INFO("LOGGER", "Project: %s v%s", PROJECT_NAME, PROJECT_VERSION);
    LOG_INFO("LOGGER", "OCPP Version: %s", OCPP_VERSION);
}

void Logger::error(const char* tag, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_ERROR, tag, format, args);
    va_end(args);
}

void Logger::warning(const char* tag, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_WARNING, tag, format, args);
    va_end(args);
}

void Logger::info(const char* tag, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_INFO, tag, format, args);
    va_end(args);
}

void Logger::debug(const char* tag, const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_DEBUG, tag, format, args);
    va_end(args);
}

void Logger::setLevel(log_level_t level) {
    currentLevel = level;
    LOG_INFO("LOGGER", "Log level changed to: %s", getLevelString(level));
}

log_level_t Logger::getLevel() {
    return currentLevel;
}

void Logger::log(log_level_t level, const char* tag, const char* format, va_list args) {
    if (!shouldLog(level)) return;
    
    // Timestamp en millisecondes
    unsigned long timestamp = millis();
    
    // Format: [TIMESTAMP] [LEVEL] [TAG] Message
    Serial.printf("[%8lu] [%5s] [%10s] ", timestamp, getLevelString(level), tag);
    
    // Message avec arguments
    char buffer[512];
    vsnprintf(buffer, sizeof(buffer), format, args);
    Serial.println(buffer);
    
    // Forcer l'écriture pour les erreurs
    if (level == LOG_LEVEL_ERROR) {
        Serial.flush();
    }
}

const char* Logger::getLevelString(log_level_t level) {
    switch (level) {
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_WARNING: return "WARN";
        case LOG_LEVEL_INFO: return "INFO";
        case LOG_LEVEL_DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}

bool Logger::shouldLog(log_level_t level) {
    return level <= currentLevel;
}
