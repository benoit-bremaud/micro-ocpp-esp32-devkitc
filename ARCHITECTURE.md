# Architecture du projet OCPP 1.6

## Structure des fonctionnalités

### Organisation par domaines OCPP

\`\`\`
features/
├── core/                    # Fonctionnalités de base OCPP
│   ├── boot_notification/
│   ├── heartbeat/
│   ├── status_notification/
│   ├── authorize/
│   ├── start_transaction/
│   ├── stop_transaction/
│   └── meter_values/
├── firmware/               # Gestion firmware
│   ├── update_firmware/
│   ├── firmware_status/
│   └── get_diagnostics/
├── local_auth/            # Autorisation locale
│   ├── get_local_list/
│   └── send_local_list/
├── remote_control/        # Contrôle à distance
│   ├── remote_start/
│   ├── remote_stop/
│   ├── unlock_connector/
│   ├── reset/
│   ├── change_availability/
│   └── change_configuration/
├── reservation/           # Réservations
│   ├── reserve_now/
│   └── cancel_reservation/
└── smart_charging/        # Charge intelligente
    ├── set_charging_profile/
    ├── clear_charging_profile/
    └── get_composite_schedule/
\`\`\`

## Règles de développement

### 1. Issue-Driven Development

- ✅ Chaque fonctionnalité doit avoir une issue GitHub
- ✅ Format des issues : `[FEATURE] Nom de la fonctionnalité`
- ✅ Labels obligatoires : `enhancement`, `ocpp-core`, `ocpp-optional`

### 2. Structure d'une fonctionnalité

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

### 3. Conventions de nommage

- Fichiers : `snake_case`
- Classes : `PascalCase`
- Fonctions : `camelCase`
- Constantes : `UPPER_CASE`
