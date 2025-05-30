# BootNotification Feature

## Issue GitHub
**#001 - [CORE] Implémentation BootNotification**

## Description
Implémentation de la fonctionnalité BootNotification selon OCPP 1.6.

## Spécification OCPP
- **Section**: 4.1 BootNotification
- **Type**: Core Feature (obligatoire)
- **Direction**: Charge Point → Central System

## Utilisation

\`\`\`cpp
#include "boot_notification_handler.h"

BootNotificationHandler handler;

// Création des données
BootNotificationHandler::BootNotificationData data;
data.chargePointVendor = "MyVendor";
data.chargePointModel = "Model1";
data.firmwareVersion = "1.0.0";

// Création de la requête
auto request = handler.createRequest(data);

// Validation
if (handler.validateRequest(request)) {
    // Envoyer la requête...
}
\`\`\`

## Tests
- ✅ Validation des champs obligatoires
- ✅ Validation des longueurs de chaînes
- ✅ Parsing des réponses
- ✅ Gestion des erreurs

## Statut
- [x] Implémentation de base
- [ ] Tests unitaires
- [ ] Intégration WebSocket
- [ ] Documentation complète
