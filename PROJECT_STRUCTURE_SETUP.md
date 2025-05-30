# [INFRA] Project Structure Setup

## 🎯 Objectif
Créer la structure de répertoires complète du projet OCPP 1.6 conforme aux Feature Profiles officiels et aux bonnes pratiques de développement ESP32/Arduino.

## 📁 Structure de Répertoires à Créer

### 1. Structure Racine
\`\`\`
micro-ocpp-esp32-devkitc/
├── docs/                   # Documentation
├── include/               # Headers globaux
├── lib/                   # Bibliothèques internes
├── src/                   # Code source principal
├── features/              # Fonctionnalités OCPP par Feature Profile
├── test/                  # Tests unitaires
├── tools/                 # Outils de développement
├── schemas/               # Schémas JSON OCPP (copie locale)
└── examples/              # Exemples d'utilisation
\`\`\`

### 2. Structure Features (Feature Profiles OCPP 1.6)
\`\`\`
features/
├── core/                    # Core Profile (obligatoire)
│   ├── authorize/
│   ├── boot_notification/
│   ├── change_availability/
│   ├── change_configuration/
│   ├── clear_cache/
│   ├── data_transfer/
│   ├── get_configuration/
│   ├── heartbeat/
│   ├── meter_values/
│   ├── remote_start_transaction/
│   ├── remote_stop_transaction/
│   ├── reset/
│   ├── start_transaction/
│   ├── status_notification/
│   ├── stop_transaction/
│   └── unlock_connector/
├── firmware/               # FirmwareManagement Profile
│   ├── diagnostics_status_notification/
│   ├── firmware_status_notification/
│   ├── get_diagnostics/
│   └── update_firmware/
├── local_auth/            # LocalAuthListManagement Profile
│   ├── get_local_list_version/
│   └── send_local_list/
├── remote_trigger/        # RemoteTrigger Profile
│   └── trigger_message/
├── reservation/           # Reservation Profile
│   ├── cancel_reservation/
│   └── reserve_now/
└── smart_charging/        # SmartCharging Profile
    ├── clear_charging_profile/
    ├── get_composite_schedule/
    └── set_charging_profile/
\`\`\`

### 3. Structure Lib (Bibliothèques Internes)
\`\`\`
lib/
├── ocpp_core/             # Core OCPP (WebSocket, JSON, etc.)
├── websocket_client/      # Client WebSocket OCPP
├── json_validator/        # Validation schémas JSON
├── storage_manager/       # Gestion stockage persistant
├── config_manager/        # Gestion configuration
├── logger/               # Système de logging
└── hardware_abstraction/ # Abstraction matérielle ESP32
\`\`\`

### 4. Structure Include (Headers Globaux)
\`\`\`
include/
├── ocpp_config.h         # Configuration globale
├── ocpp_types.h          # Types OCPP communs
├── feature_profiles.h    # Définitions Feature Profiles
└── hardware_config.h     # Configuration matérielle
\`\`\`

### 5. Structure Test
\`\`\`
test/
├── unit/                 # Tests unitaires
├── integration/          # Tests d'intégration
├── mocks/               # Objets mock
└── fixtures/            # Données de test
\`\`\`

## 🛠️ Commandes de Création

### Création de la structure racine
\`\`\`bash
mkdir -p docs include lib src features test tools schemas examples
\`\`\`

### Création des Feature Profiles
\`\`\`bash
# Core Profile
mkdir -p features/core/{authorize,boot_notification,change_availability,change_configuration,clear_cache,data_transfer,get_configuration,heartbeat,meter_values,remote_start_transaction,remote_stop_transaction,reset,start_transaction,status_notification,stop_transaction,unlock_connector}

# FirmwareManagement Profile  
mkdir -p features/firmware/{diagnostics_status_notification,firmware_status_notification,get_diagnostics,update_firmware}

# LocalAuthListManagement Profile
mkdir -p features/local_auth/{get_local_list_version,send_local_list}

# RemoteTrigger Profile
mkdir -p features/remote_trigger/trigger_message

# Reservation Profile
mkdir -p features/reservation/{cancel_reservation,reserve_now}

# SmartCharging Profile
mkdir -p features/smart_charging/{clear_charging_profile,get_composite_schedule,set_charging_profile}
\`\`\`

### Création des bibliothèques internes
\`\`\`bash
mkdir -p lib/{ocpp_core,websocket_client,json_validator,storage_manager,config_manager,logger,hardware_abstraction}
\`\`\`

### Création de la structure de test
\`\`\`bash
mkdir -p test/{unit,integration,mocks,fixtures}
\`\`\`

## 📋 Fichiers de Base à Créer

### 1. Configuration Globale
- `include/ocpp_config.h` - Configuration générale
- `include/ocpp_types.h` - Types OCPP communs
- `include/feature_profiles.h` - Définitions Feature Profiles
- `include/hardware_config.h` - Configuration ESP32

### 2. Documentation
- `docs/ARCHITECTURE.md` - Architecture du projet
- `docs/FEATURE_PROFILES.md` - Guide des Feature Profiles
- `docs/DEVELOPMENT.md` - Guide de développement
- `README.md` - Documentation principale

### 3. Configuration Projet
- `platformio.ini` - Configuration PlatformIO
- `.gitignore` - Fichiers à ignorer
- `CMakeLists.txt` - Configuration CMake (optionnel)

## ✅ Critères d'Acceptation

- [ ] Structure de répertoires créée selon les Feature Profiles OCPP 1.6
- [ ] Fichiers de configuration de base créés
- [ ] Documentation de base rédigée
- [ ] Configuration PlatformIO mise à jour
- [ ] Structure prête pour l'implémentation des fonctionnalités
- [ ] Validation de la structure avec `tree` ou `find`

## 🔗 Issues Suivantes

Cette structure prépare le terrain pour :
- [INFRA] ESP32 Hardware Configuration
- [INFRA] Logging System  
- [INFRA] WiFi Connection Manager
- [CORE] BootNotification Implementation
