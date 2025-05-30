#!/bin/bash

# Script de création de la structure de projet OCPP 1.6 avec MicroOCPP
# Issue: [INFRA] Project Structure Setup

echo "🏗️  Création de la structure de projet OCPP 1.6 avec MicroOCPP..."

# Vérifier qu'on est dans le bon répertoire
if [ ! -f "platformio.ini" ]; then
    echo "❌ Erreur: Ce script doit être exécuté depuis la racine du projet"
    exit 1
fi

# Créer la structure racine
echo "📁 Création de la structure racine..."
mkdir -p src/{config,hardware,extensions} include lib test/{unit,integration} docs examples

# Créer la structure des extensions
echo "📁 Création de la structure des extensions..."
mkdir -p src/extensions/{custom_operations,custom_callbacks,feature_profiles}

# Créer la structure des tests
echo "📁 Création de la structure des tests..."
mkdir -p test/unit test/integration

# Créer la structure de documentation
echo "📁 Création des répertoires de documentation..."
mkdir -p docs/{images,api}

# Créer les fichiers de base
echo "📝 Création des fichiers de base..."

# Fichier README principal
if [ ! -f "README.md" ]; then
    echo "# OCPP 1.6 ESP32 Implementation with MicroOCPP" > README.md
    echo "" >> README.md
    echo "Implémentation d'un point de charge OCPP 1.6 sur ESP32 en utilisant la bibliothèque MicroOCPP." >> README.md
fi

# Fichier de configuration principal
if [ ! -f "include/project_config.h" ]; then
    cat > "include/project_config.h" << EOF
#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

/**
 * @file project_config.h
 * @brief Configuration globale du projet OCPP 1.6 avec MicroOCPP
 * 
 * Issue: [INFRA] Project Structure Setup
 */

// Informations projet
#define PROJECT_NAME "micro-ocpp-esp32-devkitc"
#define PROJECT_VERSION "2.0.0"
#define OCPP_VERSION "1.6"

// Configuration ESP32
#define SERIAL_BAUD_RATE 115200

#endif // PROJECT_CONFIG_H
EOF
fi

# Fichier de configuration hardware
if [ ! -f "include/hardware_config.h" ]; then
    cat > "include/hardware_config.h" << EOF
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

/**
 * @file hardware_config.h
 * @brief Configuration hardware pour ESP32
 * 
 * Issue: [INFRA] Project Structure Setup
 */

#include <Arduino.h>

// Configuration GPIO
#define PIN_LED_STATUS 2
#define PIN_LED_ERROR 4
#define PIN_LED_WIFI 5

#endif // HARDWARE_CONFIG_H
EOF
fi

# Fichier main.cpp
if [ ! -f "src/main.cpp" ]; then
    cat > "src/main.cpp" << EOF
/**
 * @file main.cpp
 * @brief Point d'entrée principal - Intégration MicroOCPP
 * 
 * Issue: [INFRA] Project Structure Setup
 */

#include <Arduino.h>
#include <WiFi.h>
// #include <MicroOcpp.h> // Sera activé lors de l'intégration MicroOCPP

#include "project_config.h"
#include "hardware_config.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("OCPP 1.6 ESP32 Implementation with MicroOCPP");
    
    // Structure du projet initialisée
}

void loop() {
    delay(1000);
}
EOF
fi

# Fichier de documentation MicroOCPP
if [ ! -f "docs/MICROOCPP_INTEGRATION.md" ]; then
    cat > "docs/MICROOCPP_INTEGRATION.md" << EOF
# Intégration MicroOCPP

## À propos de MicroOCPP

[MicroOCPP](https://github.com/matth-x/MicroOcpp) est une bibliothèque OCPP 1.6 / 2.0.1 pour microcontrôleurs.

## Installation

MicroOCPP est installé comme dépendance PlatformIO dans notre projet.

## Documentation

- [GitHub Repository](https://github.com/matth-x/MicroOcpp)
- [Wiki](https://github.com/matth-x/MicroOcpp/wiki)
EOF
fi

# Fichier .gitignore
if [ ! -f ".gitignore" ]; then
    cat > ".gitignore" << EOF
.pio
.vscode
.DS_Store
*.swp
*.swo
EOF
fi

# Fichier platformio.ini si non existant
if [ ! -f "platformio.ini" ]; then
    cat > "platformio.ini" << EOF
; Configuration PlatformIO pour OCPP 1.6 ESP32 avec MicroOCPP
; Issue: [INFRA] Project Structure Setup

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

; Dépendances avec MicroOCPP comme bibliothèque principale
lib_deps = 
    matth-x/MicroOcpp@^2.0.1
    bblanchon/ArduinoJson@^6.21.3
    links2004/WebSockets@^2.4.0

; Configuration de monitoring
monitor_speed = 115200
EOF
fi

echo "✅ Structure de projet créée avec succès!"
echo ""
echo "📊 Résumé:"
echo "  - Structure de répertoires pour MicroOCPP"
echo "  - Fichiers de configuration de base"
echo "  - Documentation d'intégration MicroOCPP"
echo ""
echo "🚀 Prochaines étapes:"
echo "  1. Vérifier la structure avec: tree"
echo "  2. Configurer PlatformIO"
echo "  3. Implémenter l'intégration MicroOCPP"
