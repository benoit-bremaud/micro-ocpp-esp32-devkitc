# Templates d'Issues à créer

## 📁 Créer le dossier `.github/ISSUE_TEMPLATE/`

### 1. Template Core Feature
**Fichier** : `core-feature.yml`

\`\`\`yaml
name: 🔧 Core OCPP Feature
description: Implémentation d'une fonctionnalité OCPP obligatoire
title: "[CORE] "
labels: ["type:feat", "ocpp:core", "priority:critical"]
body:
  - type: markdown
    attributes:
      value: |
        ## 📋 Fonctionnalité OCPP Core
        Merci de remplir ce template pour une fonctionnalité OCPP obligatoire.
        
  - type: input
    id: ocpp_section
    attributes:
      label: Section OCPP 1.6
      description: Numéro de section dans la spécification
      placeholder: "ex: 4.1 BootNotification"
    validations:
      required: true
      
  - type: dropdown
    id: message_direction
    attributes:
      label: Direction du message
      options:
        - Charge Point → Central System
        - Central System → Charge Point
        - Bidirectionnel
    validations:
      required: true
      
  - type: textarea
    id: description
    attributes:
      label: Description
      description: Description détaillée de la fonctionnalité
    validations:
      required: true
      
  - type: checkboxes
    id: deliverables
    attributes:
      label: Livrables attendus
      options:
        - label: Handler C++ (.h + .cpp)
        - label: Schémas JSON (request + response)
        - label: Tests unitaires
        - label: Documentation README
        - label: Intégration WebSocket
\`\`\`

### 2. Template Infrastructure
**Fichier** : `infrastructure.yml`

\`\`\`yaml
name: 🏗️ Infrastructure
description: Tâche d'infrastructure technique
title: "[INFRA] "
labels: ["type:chore", "ocpp:infrastructure", "priority:high"]
body:
  - type: dropdown
    id: infra_type
    attributes:
      label: Type d'infrastructure
      options:
        - Configuration ESP32
        - WebSocket Layer
        - JSON Parser
        - Error Handling
        - Logging System
        - Memory Management
    validations:
      required: true
\`\`\`

### 3. Template Optional Feature
**Fichier** : `optional-feature.yml`

\`\`\`yaml
name: ⚡ Optional OCPP Feature
description: Fonctionnalité OCPP optionnelle
title: "[OPTIONAL] "
labels: ["type:feat", "priority:medium"]
body:
  - type: dropdown
    id: feature_category
    attributes:
      label: Catégorie
      options:
        - Remote Control
        - Firmware Management
        - Local Authorization
        - Smart Charging
        - Reservation
    validations:
      required: true
