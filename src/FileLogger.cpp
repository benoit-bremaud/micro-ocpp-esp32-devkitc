#include "FileLogger.h"
#include <SPIFFS.h>
#include <Arduino.h>
#include "Logger.h"

FileLogger::FileLogger() : currentLogIndex(0) {}

FileLogger::~FileLogger() {
    end();
}

bool FileLogger::begin() {
    if (!SPIFFS.exists("/")) { // Check if the filesystem is mounted
        Serial.println("[FileLogger] SPIFFS not mounted. Please call SPIFFS.begin() at startup.");
        return false;
    }

    openLatestLogFile();
    return true;
}

void FileLogger::end() {
    if (currentLogFile) {
        currentLogFile.flush();
        currentLogFile.close();
    }
}

void FileLogger::log(const char* message) {
    if (!currentLogFile || getLogFileSize(currentLogFile) > MAX_LOG_FILE_SIZE) {
        rotateLogFileIfNeeded();
    }

    currentLogFile.println(message);
    currentLogFile.flush();
}

void FileLogger::openLatestLogFile() {
    for (int i = 0; i < MAX_LOG_FILES; ++i) {
        String filename = getLogFileName(i);
        if (!SPIFFS.exists(filename)) {
            currentLogIndex = i;
            currentLogFile = SPIFFS.open(filename, FILE_WRITE);
            return;
        }
    }

    currentLogIndex = 0;
    currentLogFile = SPIFFS.open(getLogFileName(currentLogIndex), FILE_WRITE);
}

void FileLogger::rotateLogFileIfNeeded() {
    if (currentLogFile) {
        currentLogFile.close();
    }

    currentLogIndex = (currentLogIndex + 1) % MAX_LOG_FILES;
    deleteOldestLogFileIfNeeded();
    currentLogFile = SPIFFS.open(getLogFileName(currentLogIndex), FILE_WRITE);
}

void FileLogger::deleteOldestLogFileIfNeeded() {
    int oldestIndex = (currentLogIndex + 1) % MAX_LOG_FILES;
    String filename = getLogFileName(oldestIndex);
    if (SPIFFS.exists(filename)) {
        SPIFFS.remove(filename);
    }
}

String FileLogger::getLogFileName(int index) const {
    return String(LOG_FILE_PREFIX) + String(index) + LOG_FILE_SUFFIX;
}

size_t FileLogger::getLogFileSize(File& file) const {
    return file.size();
}
