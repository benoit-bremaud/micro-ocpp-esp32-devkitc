# Architecture du Projet OCPP 1.6

## 📋 Vue d'Ensemble

Ce projet implémente la spécification OCPP 1.6 (Edition 2) pour ESP32, en respectant fidèlement les **Feature Profiles officiels** définis par l'Open Charge Alliance (OCA).

## 🏗️ Structure du Projet

### Organisation par Feature Profiles OCPP 1.6

\`\`\`
micro-ocpp-esp32-devkitc/
├── features/                    # Fonctionnalités OCPP par Feature Profile
│   ├── core/                   # Core Profile (obligatoire)
│   ├── firmware/               # FirmwareManagement Profile
│   ├── local_auth/            # LocalAuthListManagement Profile
│   ├── remote_trigger/        # RemoteTrigger Profile
│   ├── reservation/           # Reservation Profile
│   └── smart_charging/        # SmartCharging Profile
├── lib/                       # Bibliothèques internes
├── include/                   # Headers globaux
├── src/                       # Code source principal
├── test/                      # Tests unitaires et d'intégration
├── docs/                      # Documentation
├── schemas/                   # Schémas JSON OCPP
└── examples/                  # Exemples d'utilisation
\`\`\`

## 📊 Feature Profiles OCPP 1.6

### 1. Core Profile (Obligatoire)
**Description**: Fonctionnalités de base comparables à OCPP 1.5

**Messages Charge Point → Central System**:
- `Authorize` - Autorisation d'un idTag
- `BootNotification` - Notification de démarrage
- `DataTransfer` - Transfert de données vendor-specific
- `Heartbeat` - Signal de vie
- `MeterValues` - Valeurs de compteur
- `StartTransaction` - Démarrage de transaction
- `StatusNotification` - Notification de statut
- `StopTransaction` - Arrêt de transaction

**Messages Central System → Charge Point**:
- `ChangeAvailability` - Changement de disponibilité
- `ChangeConfiguration` - Changement de configuration
- `ClearCache` - Effacement du cache
- `DataTransfer` - Transfert de données vendor-specific
- `GetConfiguration` - Récupération de configuration
- `RemoteStartTransaction` - Démarrage à distance
- `RemoteStopTransaction` - Arrêt à distance
- `Reset` - Redémarrage
- `UnlockConnector` - Déverrouillage connecteur

### 2. FirmwareManagement Profile (Optionnel)
**Description**: Support pour la gestion des mises à jour firmware et téléchargement de logs de diagnostic

**Messages**:
- `UpdateFirmware` (CS → CP)
- `FirmwareStatusNotification` (CP → CS)
- `GetDiagnostics` (CS → CP)
- `DiagnosticsStatusNotification` (CP → CS)

### 3. LocalAuthListManagement Profile (Optionnel)
**Description**: Fonctionnalités pour gérer la liste d'autorisation locale

**Messages**:
- `GetLocalListVersion` (CS → CP)
- `SendLocalList` (CS → CP)

### 4. RemoteTrigger Profile (Optionnel)
**Description**: Déclenchement à distance de messages

**Messages**:
- `TriggerMessage` (CS → CP)

### 5. Reservation Profile (Optionnel)
**Description**: Système de réservation des points de charge

**Messages**:
- `ReserveNow` (CS → CP)
- `CancelReservation` (CS → CP)

### 6. SmartCharging Profile (Optionnel)
**Description**: Charge intelligente avec profils de charge

**Messages**:
- `SetChargingProfile` (CS → CP)
- `ClearChargingProfile` (CS → CP)
- `GetCompositeSchedule` (CS → CP)

## 🔧 Architecture Technique

### Couches Logicielles

\`\`\`
┌─────────────────────────────────────────┐
│           Application Layer             │
│        (Features OCPP 1.6)            │
├─────────────────────────────────────────┤
│           OCPP Protocol Layer          │
│     (Message Handling, Validation)     │
├─────────────────────────────────────────┤
│          Transport Layer               │
│        (WebSocket, JSON)               │
├─────────────────────────────────────────┤
│          Network Layer                 │
│           (WiFi, TCP/IP)               │
├─────────────────────────────────────────┤
│         Hardware Layer                 │
│           (ESP32, GPIO)                │
└─────────────────────────────────────────┘
\`\`\`

### Bibliothèques Internes

- **ocpp_core**: Gestion des messages OCPP, validation, routing
- **websocket_client**: Client WebSocket pour communication OCPP-J
- **json_validator**: Validation des messages contre les schémas JSON
- **storage_manager**: Stockage persistant (configuration, cache, transactions)
- **config_manager**: Gestion de la configuration système
- **logger**: Système de logging multi-niveaux
- **hardware_abstraction**: Abstraction matérielle ESP32

## 📋 Règles de Développement

### 1. Issue-Driven Development
- ✅ Chaque fonctionnalité doit avoir une issue GitHub
- ✅ Format des issues : `[CATEGORY] Nom de la fonctionnalité`
- ✅ Labels obligatoires : `type:feat`, `ocpp:profile`, `priority:level`

### 2. Structure d'une Fonctionnalité
\`\`\`
feature_name/
├── README.md              # Documentation de la fonctionnalité
├── feature_handler.h      # Interface publique
├── feature_handler.cpp    # Implémentation
├── schemas/              # Schémas JSON OCPP
│   ├── request.json
│   └── response.json
└── tests/                # Tests unitaires
    └── test_feature.cpp
\`\`\`

### 3. Conventions de Nommage
- **Fichiers**: `snake_case`
- **Classes**: `PascalCase`
- **Fonctions**: `camelCase`
- **Constantes**: `UPPER_CASE`
- **Variables**: `camelCase`

### 4. Standards de Qualité
- **Couverture de tests**: Minimum 80%
- **Documentation**: Headers Doxygen obligatoires
- **Validation**: Conformité schémas OCPP 1.6
- **Mémoire**: Pas de fuites mémoire
- **Performance**: Temps de réponse < 100ms

## 🚀 Roadmap d'Implémentation

### Phase 1: Infrastructure (2-3 semaines)
1. **Foundation Setup** - Structure projet, configuration
2. **Network & Communication** - WiFi, WebSocket
3. **Data Management** - Stockage, validation JSON
4. **Testing & Monitoring** - Framework tests, monitoring

### Phase 2: Core Profile (3-4 semaines)
1. **Authentication & Boot** - BootNotification, Heartbeat, Authorize
2. **Transactions** - StartTransaction, StopTransaction, MeterValues
3. **Monitoring** - StatusNotification, DataTransfer

### Phase 3: Optional Profiles (4-6 semaines)
1. **Remote Control** - Remote Start/Stop, Reset, Configuration
2. **Firmware Management** - Update, Diagnostics
3. **Advanced Features** - Local Auth, Smart Charging, Reservations

## 📚 Références

- **OCPP 1.6 Specification** - Open Charge Alliance
- **OCPP-J 1.6 Specification** - JSON Implementation
- **ESP32 Documentation** - Espressif Systems
- **PlatformIO Documentation** - PlatformIO Core

## 🔗 Liens Utiles

- [Repository GitHub](https://github.com/benoit-bremaud/micro-ocpp-esp32-devkitc)
- [Issues Tracker](https://github.com/benoit-bremaud/micro-ocpp-esp32-devkitc/issues)
- [Projects Board](https://github.com/users/benoit-bremaud/projects)
- [OCPP 1.6 Documentation](./OCPP_1.6_documentation/)
