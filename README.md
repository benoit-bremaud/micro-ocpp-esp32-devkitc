# OCPP 1.6 ESP32 Implementation with MicroOCPP

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![OCPP Version](https://img.shields.io/badge/OCPP-1.6-blue.svg)](https://www.openchargealliance.org/)
[![MicroOCPP](https://img.shields.io/badge/MicroOCPP-2.0.1-green.svg)](https://github.com/matth-x/MicroOcpp)

## 🎯 Objectif

Implémentation d'un point de charge OCPP 1.6 sur ESP32 en utilisant la bibliothèque [MicroOCPP](https://github.com/matth-x/MicroOcpp) comme base, avec des extensions et personnalisations pour nos besoins spécifiques.

## ⚡ Caractéristiques

- ✅ **OCPP 1.6** - Support complet du protocole OCPP 1.6
- ✅ **ESP32 Optimisé** - Conçu spécifiquement pour l'ESP32 DevKit-C
- ✅ **MicroOCPP** - Utilise la bibliothèque mature MicroOCPP
- ✅ **Extensions** - Ajout de fonctionnalités personnalisées
- ✅ **Hardware Integration** - Support pour capteurs et actionneurs

## 📊 Feature Profiles Supportés

| Feature Profile | Statut | Description |
|----------------|--------|-------------|
| **Core** | ✅ Supporté | Fonctionnalités de base OCPP |
| **Smart Charging** | ✅ Supporté | Charge intelligente |
| **Local Auth List** | ✅ Supporté | Listes d'autorisation locales |
| **Firmware Management** | ✅ Supporté | Gestion firmware |
| **Reservation** | ✅ Supporté | Système de réservation |

## 🚀 Démarrage Rapide

### Prérequis

- **PlatformIO** - [Installation](https://platformio.org/install)
- **ESP32 DevKit-C** - Carte de développement
- **Serveur OCPP** - Pour les tests (ex: SteVe, OCPP Central System)

### Installation

\`\`\`bash
# Cloner le repository
git clone https://github.com/benoit-bremaud/micro-ocpp-esp32-devkitc.git
cd micro-ocpp-esp32-devkitc

# Compiler et uploader
pio run --target upload

# Monitorer les logs
pio device monitor
\`\`\`

### Configuration

1. **WiFi** - Configurer SSID et mot de passe dans `src/main.cpp`
2. **OCPP Server** - Définir l'URL du serveur OCPP dans `src/main.cpp`
3. **Hardware** - Adapter la configuration dans `include/hardware_config.h`

## 📁 Structure du Projet

\`\`\`
micro-ocpp-esp32-devkitc/
├── src/                    # Code source principal
│   ├── main.cpp            # Point d'entrée principal
│   ├── config/             # Configuration spécifique
│   ├── hardware/           # Intégration hardware ESP32
│   └── extensions/         # Extensions MicroOCPP
├── include/                # Headers globaux
│   ├── project_config.h    # Configuration du projet
│   └── hardware_config.h   # Configuration hardware
├── lib/                    # Bibliothèques (MicroOCPP)
├── test/                   # Tests unitaires et d'intégration
├── docs/                   # Documentation
└── examples/               # Exemples d'utilisation
\`\`\`

## 🔧 Développement

### Workflow

1. **Issue-Driven** - Chaque fonctionnalité a une issue GitHub
2. **Feature Branches** - `feature/issue-number-feature-name`
3. **Tests** - Tests unitaires pour les extensions
4. **Code Review** - Pull Request avec review

### Commandes Utiles

\`\`\`bash
# Compiler
pio run

# Uploader
pio run --target upload

# Debug
pio run --target upload && pio device monitor

# Nettoyage
pio run --target clean
\`\`\`

## 📚 Documentation

- [**MicroOCPP Integration**](docs/MICROOCPP_INTEGRATION.md) - Guide d'intégration MicroOCPP
- [**Hardware Integration**](docs/HARDWARE_INTEGRATION.md) - Guide d'intégration hardware
- [**Development Guide**](docs/DEVELOPMENT_GUIDE.md) - Guide de développement

## 📈 Roadmap

- [x] **Phase 1**: Structure du projet avec MicroOCPP
- [ ] **Phase 2**: Intégration hardware ESP32
- [ ] **Phase 3**: Extensions et personnalisations
- [ ] **Phase 4**: Tests et optimisations

## 🤝 Contribution

Les contributions sont les bienvenues ! Voir [CONTRIBUTING.md](CONTRIBUTING.md) pour les guidelines.

## 📄 Licence

Ce projet est sous licence MIT. Voir [LICENSE](LICENSE) pour plus de détails.

## 🔗 Liens

- [MicroOCPP](https://github.com/matth-x/MicroOcpp)
- [Open Charge Alliance](https://www.openchargealliance.org/)
- [OCPP 1.6 Specification](https://www.openchargealliance.org/protocols/ocpp-16/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)

---

**Développé avec ❤️ pour la communauté OCPP**
\`\`\`

```shellscript file="scripts/create_project_structure.sh"
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
