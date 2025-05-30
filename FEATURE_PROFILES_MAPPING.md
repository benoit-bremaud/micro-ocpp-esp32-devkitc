# OCPP 1.6 Feature Profiles - Mapping Officiel

## 📋 Feature Profiles Officiels

D'après la documentation OCPP 1.6 (Section 3.3), les Feature Profiles sont :

1. **Core** - Fonctionnalités de base obligatoires
2. **FirmwareManagement** - Gestion firmware et diagnostics  
3. **LocalAuthListManagement** - Gestion listes d'autorisation locales
4. **Reservation** - Système de réservation
5. **SmartCharging** - Charge intelligente
6. **RemoteTrigger** - Déclenchement à distance

## 🗂️ Mapping des Messages par Feature Profile

### Core Profile (Obligatoire)
#### Charge Point → Central System
- `Authorize` - Autorisation d'un idTag
- `BootNotification` - Notification de démarrage
- `DataTransfer` - Transfert de données vendor-specific
- `Heartbeat` - Signal de vie
- `MeterValues` - Valeurs de compteur
- `StartTransaction` - Démarrage de transaction
- `StatusNotification` - Notification de statut
- `StopTransaction` - Arrêt de transaction

#### Central System → Charge Point
- `ChangeAvailability` - Changement de disponibilité
- `ChangeConfiguration` - Changement de configuration
- `ClearCache` - Effacement du cache
- `DataTransfer` - Transfert de données vendor-specific
- `GetConfiguration` - Récupération de configuration
- `RemoteStartTransaction` - Démarrage à distance
- `RemoteStopTransaction` - Arrêt à distance
- `Reset` - Redémarrage
- `UnlockConnector` - Déverrouillage connecteur

### FirmwareManagement Profile
#### Central System → Charge Point
- `UpdateFirmware` - Mise à jour firmware
- `GetDiagnostics` - Récupération diagnostics

#### Charge Point → Central System
- `FirmwareStatusNotification` - Statut mise à jour firmware
- `DiagnosticsStatusNotification` - Statut diagnostics

### LocalAuthListManagement Profile
#### Central System → Charge Point
- `GetLocalListVersion` - Version liste locale
- `SendLocalList` - Envoi liste locale

### Reservation Profile
#### Central System → Charge Point
- `ReserveNow` - Création réservation
- `CancelReservation` - Annulation réservation

### SmartCharging Profile
#### Central System → Charge Point
- `SetChargingProfile` - Définition profil de charge
- `ClearChargingProfile` - Effacement profil de charge
- `GetCompositeSchedule` - Récupération planning composite

### RemoteTrigger Profile
#### Central System → Charge Point
- `TriggerMessage` - Déclenchement message

## 📁 Structure de Répertoires Recommandée

\`\`\`
features/
├── core/                    # Core Profile
├── firmware/               # FirmwareManagement Profile
├── local_auth/            # LocalAuthListManagement Profile
├── remote_trigger/        # RemoteTrigger Profile
├── reservation/           # Reservation Profile
└── smart_charging/        # SmartCharging Profile
\`\`\`

Cette structure respecte exactement les Feature Profiles définis dans la spécification OCPP 1.6.
