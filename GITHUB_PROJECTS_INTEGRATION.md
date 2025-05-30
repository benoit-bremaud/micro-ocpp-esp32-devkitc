# Intégration avec les projets GitHub

## Projets GitHub associés
- **Projet #16** : `https://github.com/users/benoit-bremaud/projects/16`
- **Projet #22** : `https://github.com/users/benoit-bremaud/projects/22`
- **Repository** : `https://github.com/benoit-bremaud/micro-ocpp-esp32-devkitc`

## Organisation des issues par fonctionnalités OCPP

### Labels recommandés
\`\`\`yaml
# Catégories OCPP
- name: "ocpp-core"
  color: "d73a4a"
  description: "Fonctionnalités OCPP obligatoires"

- name: "ocpp-firmware"
  color: "0075ca"
  description: "Gestion firmware et diagnostics"

- name: "ocpp-local-auth"
  color: "cfd3d7"
  description: "Autorisation locale"

- name: "ocpp-remote-control"
  color: "a2eeef"
  description: "Contrôle à distance"

- name: "ocpp-reservation"
  color: "7057ff"
  description: "Système de réservation"

- name: "ocpp-smart-charging"
  color: "008672"
  description: "Charge intelligente"

# Priorités
- name: "priority-high"
  color: "d93f0b"
  description: "Priorité haute"

- name: "priority-medium"
  color: "fbca04"
  description: "Priorité moyenne"

- name: "priority-low"
  color: "0e8a16"
  description: "Priorité basse"

# Statuts
- name: "status-blocked"
  color: "b60205"
  description: "Bloqué par une dépendance"

- name: "status-in-progress"
  color: "fbca04"
  description: "En cours de développement"

- name: "status-review"
  color: "0052cc"
  description: "En attente de review"
\`\`\`

## Templates d'issues

### Template pour fonctionnalité OCPP Core
\`\`\`markdown
---
name: Fonctionnalité OCPP Core
about: Implémentation d'une fonctionnalité OCPP obligatoire
title: '[CORE] '
labels: 'ocpp-core, enhancement, priority-high'
assignees: 'benoit-bremaud'
projects: ['benoit-bremaud/16']
---

## 📋 Description
Implémentation de la fonctionnalité OCPP 1.6 : **[NOM_FONCTIONNALITE]**

## 📖 Référence OCPP
- **Section** : [Numéro de section]
- **Type** : Core Feature (obligatoire)
- **Direction** : [Charge Point → Central System / Central System → Charge Point]

## 🎯 Objectifs
- [ ] Implémentation du handler
- [ ] Validation des schémas JSON
- [ ] Tests unitaires (couverture > 80%)
- [ ] Documentation

## ✅ Critères d'acceptation
- [ ] Conforme à la spécification OCPP 1.6
- [ ] Validation des champs obligatoires
- [ ] Gestion des erreurs
- [ ] Tests passants

## 🏗️ Structure attendue
\`\`\`
features/core/[nom_fonctionnalite]/
├── README.md
├── [nom]_handler.h
├── [nom]_handler.cpp
├── schemas/
│   ├── request.json
│   └── response.json
└── tests/
    └── test_[nom].cpp
\`\`\`

## 🔗 Liens
- [ ] Schéma JSON request : `schemas/json/[Nom].json`
- [ ] Schéma JSON response : `schemas/json/[Nom]Response.json`
- [ ] Documentation OCPP : Section [X.X]
\`\`\`

### Template pour fonctionnalité optionnelle
\`\`\`markdown
---
name: Fonctionnalité OCPP Optionnelle
about: Implémentation d'une fonctionnalité OCPP optionnelle
title: '[OPTIONAL] '
labels: 'ocpp-optional, enhancement, priority-medium'
assignees: 'benoit-bremaud'
projects: ['benoit-bremaud/22']
---

## 📋 Description
Implémentation de la fonctionnalité OCPP 1.6 optionnelle : **[NOM_FONCTIONNALITE]**

## 📖 Référence OCPP
- **Section** : [Numéro de section]
- **Type** : Optional Feature
- **Catégorie** : [Firmware/LocalAuth/RemoteControl/Reservation/SmartCharging]

## 🎯 Objectifs
- [ ] Analyse de faisabilité
- [ ] Implémentation du handler
- [ ] Tests unitaires
- [ ] Documentation

## 💡 Valeur ajoutée
[Expliquer pourquoi cette fonctionnalité est importante pour le projet]

## 🔗 Dépendances
- [ ] Issue #[X] - [Fonctionnalité dépendante]
