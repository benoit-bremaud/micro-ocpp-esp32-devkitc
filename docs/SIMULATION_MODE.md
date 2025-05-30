# Mode Simulation pour ESP32 DOIT DevKitC

## 📋 Introduction

Le mode simulation permet de tester le code sans avoir tous les capteurs et composants connectés. Dans ce mode, seule la LED bleue intégrée (GPIO2) est utilisée, et tous les autres composants sont simulés par logiciel.

## 🔧 Configuration

Le mode simulation est activé par la définition `SIMULATION_MODE` dans le fichier `hardware_config.h` ou via les flags de compilation dans `platformio.ini`.

\`\`\`ini
build_flags = 
    -I include
    -I src/hardware
    -D SIMULATION_MODE=1
\`\`\`

## 💡 Fonctionnalités simulées

### Capteurs
- **Courant** : Valeurs aléatoires entre `SIM_CURRENT_MIN` et `SIM_CURRENT_MAX`
- **Tension** : Valeurs aléatoires entre `SIM_VOLTAGE_MIN` et `SIM_VOLTAGE_MAX`
- **Température** : Valeurs aléatoires entre `SIM_TEMP_MIN` et `SIM_TEMP_MAX`

### Composants
- **LEDs** : Seule la LED bleue est réelle, les autres sont simulées par des messages
- **Relais** : Simulés par des messages dans la console
- **Boutons** : Simulés aléatoirement (1% de chance d'être pressés)
- **Buzzer** : Simulé par des messages dans la console

## 🚀 Utilisation

### Patterns de LED

La LED bleue intégrée est utilisée pour indiquer différents états :

1. **État INIT** : Clignotement rapide (200ms)
2. **État READY** : Clignotement lent (1000ms)
3. **État CHARGING** : Clignotement moyen (500ms)
4. **État ERROR** : Pattern SOS (... --- ...)
5. **État MAINTENANCE** : Double clignotement

### Cycle de démonstration

Le programme change automatiquement d'état toutes les 30 secondes pour démontrer les différents patterns de LED :

\`\`\`
READY → CHARGING → MAINTENANCE → ERROR → READY
\`\`\`

### Mesures simulées

Les mesures simulées sont affichées dans la console toutes les 2 secondes :

\`\`\`
📊 [   12345] Measurements (SIMULATED):
    Current L1: 8.45 A
    Current L2: 7.23 A
    Voltage: 230.50 V
    Temperature: 35.20 °C
    Power: 3612.24 W
    Energy: 1.25 Wh
\`\`\`

## 🔍 Débogage

En mode simulation, des messages supplémentaires sont affichés dans la console pour indiquer les actions simulées :

\`\`\`
💡 [SIM] LED WiFi ALLUMÉE
🔌 [SIM] Contacteur FERMÉ
🔊 [SIM] Buzzer activé pendant 100 ms
\`\`\`

## 🛠️ Transition vers le mode réel

Pour désactiver le mode simulation et utiliser les composants réels :

1. Commentez ou supprimez la ligne `#define SIMULATION_MODE 1` dans `hardware_config.h`
2. Ou supprimez `-D SIMULATION_MODE=1` dans `platformio.ini`
3. Recompilez et téléversez le code

## ⚠️ Précautions

- Assurez-vous que tous les composants sont correctement connectés avant de désactiver le mode simulation
- Testez progressivement chaque composant en les connectant un par un
- Vérifiez les tensions et polarités avant de connecter des composants sensibles
