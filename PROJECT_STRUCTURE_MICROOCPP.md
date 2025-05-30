# Structure du Projet avec MicroOCPP

## 📋 Objectif
Créer une structure de projet optimale pour utiliser MicroOCPP comme bibliothèque principale pour notre implémentation OCPP 1.6 sur ESP32.

## 📁 Structure de Répertoires Proposée

### Structure Racine
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
├── lib/                    # Bibliothèques (MicroOCPP sera ici)
├── test/                   # Tests unitaires et d'intégration
├── docs/                   # Documentation
└── examples/               # Exemples d'utilisation
\`\`\`

### Structure src/
\`\`\`
src/
├── main.cpp                # Point d'entrée principal
├── config/                 # Configuration
│   ├── ocpp_config.cpp     # Configuration OCPP
│   └── wifi_config.cpp     # Configuration WiFi
├── hardware/               # Intégration hardware
│   ├── esp32_gpio.cpp      # Gestion GPIO ESP32
│   ├── esp32_led.cpp       # Gestion LEDs
│   └── esp32_monitor.cpp   # Monitoring système
└── extensions/             # Extensions MicroOCPP
    ├── custom_operations/  # Opérations personnalisées
    ├── custom_callbacks/   # Callbacks personnalisés
    └── feature_profiles/   # Extensions Feature Profiles
\`\`\`

### Structure include/
\`\`\`
include/
├── project_config.h        # Configuration globale du projet
├── hardware_config.h       # Configuration hardware
└── extensions/             # Headers des extensions
    ├── custom_operations.h # Opérations personnalisées
    └── custom_callbacks.h  # Callbacks personnalisés
\`\`\`

### Structure lib/
\`\`\`
lib/
├── README.md               # Instructions pour les bibliothèques
└── .gitkeep                # MicroOCPP sera installé ici via PlatformIO
\`\`\`

## 🛠️ Configuration PlatformIO

Le fichier `platformio.ini` doit être configuré pour utiliser MicroOCPP comme dépendance principale :

\`\`\`ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

; Dépendances
lib_deps = 
    matth-x/MicroOcpp@^2.0.1    ; Bibliothèque OCPP principale
    bblanchon/ArduinoJson@^6.21.3
    links2004/WebSockets@^2.4.0

; Configuration des chemins sources
build_src_filter = 
    +<*>
    +<../src/**/*.cpp>

; Chemins d'inclusion
build_flags = 
    -I include
    -I src/config
    -I src/hardware
    -I src/extensions
    -D PROJECT_VERSION=\"2.0.0\"
    -D OCPP_VERSION=\"1.6\"

; Configuration de monitoring
monitor_speed = 115200
\`\`\`

## 📋 Fichiers de Base à Créer

### 1. Point d'entrée principal
- `src/main.cpp` - Initialisation et boucle principale

### 2. Configuration
- `include/project_config.h` - Configuration globale
- `include/hardware_config.h` - Configuration hardware ESP32

### 3. Documentation
- `README.md` - Documentation principale
- `docs/MICROOCPP_INTEGRATION.md` - Guide d'intégration MicroOCPP

## 🔄 Workflow Git

1. **Branche principale** : `main`
2. **Branche de développement** : `develop`
3. **Branches de fonctionnalités** : `feature/issue-number-feature-name`
4. **Branches de correction** : `fix/issue-number-bug-name`

## 📦 Gestion des Dépendances

### MicroOCPP
MicroOCPP sera géré comme une dépendance PlatformIO, ce qui permet :
- Mise à jour facile
- Gestion des versions
- Pas besoin de copier le code source

### Autres Dépendances
- ArduinoJson
- WebSockets
- Autres bibliothèques nécessaires

## 🚀 Prochaines Étapes

1. **Créer la structure de répertoires**
2. **Configurer PlatformIO**
3. **Créer les fichiers de base**
4. **Documenter l'intégration MicroOCPP**
