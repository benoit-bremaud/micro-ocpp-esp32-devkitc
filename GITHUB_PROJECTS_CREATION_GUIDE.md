# Guide de Création des Projets GitHub

## 📋 Projets à créer (dans l'ordre)

### 1. Projet Principal : "OCPP Core Features"
- **Nom** : `OCPP Core Features`
- **Description** : `Fonctionnalités OCPP 1.6 obligatoires - MVP`
- **Vue** : Kanban
- **Colonnes** :
  - 📋 Backlog
  - 🔍 Analysis  
  - 🚧 In Progress
  - 🔎 Review
  - ✅ Done

### 2. Projet Infrastructure : "OCPP Infrastructure"
- **Nom** : `OCPP Infrastructure`
- **Description** : `Base technique, WebSocket, configuration ESP32`
- **Vue** : Kanban
- **Colonnes** : (identiques)

### 3. Projet Remote Control : "OCPP Remote Control"
- **Nom** : `OCPP Remote Control`
- **Description** : `Contrôle à distance des points de charge`

### 4. Projet Firmware : "OCPP Firmware Management"
- **Nom** : `OCPP Firmware Management`
- **Description** : `Gestion firmware et diagnostics`

### 5. Projet Local Auth : "OCPP Local Authorization"
- **Nom** : `OCPP Local Authorization`
- **Description** : `Autorisation locale et listes blanches`

### 6. Projet Smart Charging : "OCPP Smart Charging"
- **Nom** : `OCPP Smart Charging`
- **Description** : `Profils de charge et optimisation`

### 7. Projet Reservation : "OCPP Reservation"
- **Nom** : `OCPP Reservation`
- **Description** : `Système de réservation des bornes`

## 🏷️ Labels à créer dans le repository

### Labels par Type
\`\`\`yaml
type:feat - #0e8a16 - Nouvelle fonctionnalité
type:fix - #d73a4a - Correction de bug
type:docs - #0075ca - Documentation
type:chore - #fef2c0 - Maintenance
type:test - #f9d0c4 - Tests
\`\`\`

### Labels par Domaine OCPP
\`\`\`yaml
ocpp:core - #b60205 - Fonctionnalités core OCPP
ocpp:infrastructure - #5319e7 - Infrastructure technique
ocpp:remote - #fbca04 - Contrôle à distance
ocpp:firmware - #0052cc - Gestion firmware
ocpp:auth - #006b75 - Autorisation locale
ocpp:charging - #1d76db - Charge intelligente
ocpp:reservation - #0e8a16 - Réservations
\`\`\`

### Labels par Priorité
\`\`\`yaml
priority:critical - #b60205 - Critique (MVP)
priority:high - #d93f0b - Haute
priority:medium - #fbca04 - Moyenne
priority:low - #0e8a16 - Basse
