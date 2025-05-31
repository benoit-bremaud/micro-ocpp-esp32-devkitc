/**
* @file main_simple.cpp
* @brief Version simplifiée pour debug
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* Version debug minimaliste
*/

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

#include "Logger.h"
#include "log_macros.h"
#include "FileLogger.h"

// Configuration simple
#define LED_STATUS_PIN 2
#define SERIAL_BAUD_RATE 115200

// Variables globales
unsigned long lastBlink = 0;
unsigned long lastHeartbeat = 0;
bool ledState = false;

void printLogFile(const char* filename) {
    File file = SPIFFS.open(filename, FILE_READ);
    if (file) {
        Serial.printf("\n📄 Contenu de %s :\n", filename);
        while (file.available()) {
            Serial.write(file.read());
        }
        file.close();
    } else {
        Serial.printf("❌ Impossible d'ouvrir %s\n", filename);
    }
}


void setup() {
    // Initialisation série avec délai
    Serial.begin(SERIAL_BAUD_RATE);

    Logger::getInstance().begin(true); // Initialisation du logger
    
    Logger::getInstance().setLevel(LOG_LEVEL_INFO);
    LOG_DEBUG("Debug: Should NOT appear at INFO level");
    LOG_INFO("Info: Should appear");
    LOG_WARN("Warning: Should appear");
    LOG_ERROR("Error: Should appear");

    Logger::getInstance().setLevel(LOG_LEVEL_DEBUG);
    LOG_DEBUG("Debug: Should appear at DEBUG level");
    
    delay(2000); // Attendre que le port série soit stable
    
    Serial.println();
    Serial.println("=================================");
    Serial.println("ESP32 DEBUG MODE - Version Simple");
    Serial.println("=================================");
    
    // Configuration des pins
    pinMode(LED_STATUS_PIN, OUTPUT);
    digitalWrite(LED_STATUS_PIN, LOW);
    
    // Test de base
    Serial.println("✅ Initialisation série OK");
    Serial.printf("CPU Freq: %d MHz\n", getCpuFrequencyMhz());
    Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Flash Size: %d MB\n", ESP.getFlashChipSize() / (1024 * 1024));
    
    // Test LED
    Serial.println("🔵 Test LED...");
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_STATUS_PIN, HIGH);
        delay(200);
        digitalWrite(LED_STATUS_PIN, LOW);
        delay(200);
        Serial.printf("  Blink %d/5\n", i + 1);
    }
    
    Serial.println("🚀 Démarrage de la boucle principale...");
    lastBlink = millis();
    lastHeartbeat = millis();
}

void loop() {
    unsigned long now = millis();
    
    // Clignotement LED toutes les secondes
    if (now - lastBlink >= 1000) {
        ledState = !ledState;
        digitalWrite(LED_STATUS_PIN, ledState);
        lastBlink = now;
    }
    
    // Affichage du heartbeat toutes les 5 secondes
    if (now - lastHeartbeat >= 5000) {
        LOG_INFO("❤️ Heartbeat: ESP32 is alive!");
        lastHeartbeat = now;
    }

    // Affichage du log
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        if (input.startsWith("log ")) {
            String filename = input.substring(4);
            if (filename.length() > 0) {
                printLogFile(filename.c_str());
            } else {
                Serial.println("❌ Veuillez spécifier un nom de fichier.");
            }
        } else {
            Serial.printf("📥 Commande reçue: %s\n", input.c_str());
        }
    }

    
    // Petite pause
    delay(10);
}
