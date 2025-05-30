# Guide d'Intégration Hardware ESP32 DOIT DevKitC

## 🎯 Objectif

Ce guide détaille l'intégration hardware pour le projet OCPP 1.6 sur ESP32 DOIT DevKitC, incluant la configuration des GPIO, capteurs et actionneurs nécessaires pour un point de charge.

## 🔧 ESP32 DOIT DevKitC - Spécifications

### Caractéristiques Principales
- **MCU**: ESP32-WROOM-32D
- **USB-Serial**: CH340 (VID:PID=1A86:7523)
- **GPIO**: 30 broches disponibles
- **ADC**: 2 ADC 12-bit (18 canaux)
- **PWM**: 16 canaux
- **UART**: 3 interfaces
- **SPI**: 4 interfaces
- **I2C**: 2 interfaces

### Pinout Utilisé

\`\`\`
                    ESP32 DOIT DevKitC
                    ┌─────────────────┐
                    │  ┌───────────┐  │
                    │  │           │  │
                    │  │   ESP32   │  │
                    │  │           │  │
                    │  └───────────┘  │
                    │                 │
    3V3  ┌──────────┤ 3V3         VIN ├──────────┐ 5V
    GND  ┌──────────┤ GND         GND ├──────────┐ GND
    LED Status ──────┤ IO2         IO4 ├────────── LED Error
    LED WiFi ────────┤ IO5        IO16 ├────────── RFID RX
    Buzzer ──────────┤ IO26       IO17 ├────────── RFID TX
    Door Sensor ─────┤ IO27       IO18 ├────────── LED Charging
    Emergency Btn ───┤ IO12       IO19 ├────────── Relay Contactor
    Start Btn ───────┤ IO13       IO21 ├────────── Relay Lock
    Stop Btn ────────┤ IO14       IO22 ├────────── Relay Pilot
    Earth Fault ─────┤ IO15       IO23 ├──────────
    RFID Enable ─────┤ IO25       IO32 ├────────── Voltage Sensor (ADC)
                     ┤ IO33       IO33 ├────────── Temperature Sensor (ADC)
    Current L1 ──────┤ IO34       IO35 ├────────── Current L2 (ADC)
                     └─────────────────┘
\`\`\`

## 📊 Configuration des Capteurs

### Capteurs de Courant (ACS712-30A)
- **Type**: Capteur à effet Hall
- **Plage**: 0-30A AC/DC
- **Sensibilité**: 66mV/A
- **Tension de sortie**: VCC/2 ± (Courant × Sensibilité)
- **Pins**: GPIO34 (L1), GPIO35 (L2)

### Capteur de Tension
- **Type**: Diviseur résistif
- **Plage**: 0-250V AC
- **Ratio**: 1:56 (250V → 4.46V)
- **Protection**: Fusible + varistance
- **Pin**: GPIO32

### Capteur de Température
- **Type**: NTC 10kΩ
- **Plage**: -20°C à +80°C
- **Pull-up**: 10kΩ
- **Pin**: GPIO33

## 🔌 Configuration des Actionneurs

### Relais Contacteur Principal
- **Type**: Relais 32A 230V AC
- **Commande**: 3.3V/5V DC
- **Protection**: Diode de roue libre
- **Pin**: GPIO19

### Relais Verrouillage
- **Type**: Relais 5A 12V DC
- **Fonction**: Verrouillage mécanique du connecteur
- **Pin**: GPIO21

### Relais Signal Pilote
- **Type**: Relais pour commutation signal pilote
- **Fonction**: Contrôle PWM signal pilote
- **Pin**: GPIO22

## 💡 Configuration des LEDs

### LED de Statut (Intégrée)
- **Couleur**: Bleue
- **Pin**: GPIO2 (LED intégrée ESP32)
- **Fonction**: Indication état général

### LED d'Erreur
- **Couleur**: Rouge
- **Pin**: GPIO4
- **Fonction**: Indication erreurs/alarmes

### LED WiFi
- **Couleur**: Verte
- **Pin**: GPIO5
- **Fonction**: État connexion WiFi

### LED Charge
- **Couleur**: Orange
- **Pin**: GPIO18
- **Fonction**: Indication charge en cours

## 🔘 Interface Utilisateur

### Boutons
- **Start**: GPIO13 (Pull-up interne)
- **Stop**: GPIO14 (Pull-up interne)
- **Emergency**: GPIO12 (Pull-up interne)

### Buzzer
- **Type**: Buzzer piézo 3.3V
- **Pin**: GPIO26
- **Fonction**: Feedback sonore

## 🛡️ Sécurité

### Capteurs de Sécurité
- **Porte ouverte**: GPIO27 (Contact NO)
- **Défaut terre**: GPIO15 (Relais différentiel)

### Seuils de Sécurité
- **Courant max**: 35A (seuil alarme)
- **Tension min/max**: 200V - 250V
- **Température max**: 70°C

## 📡 Communication

### RFID Reader
- **Interface**: UART2
- **Baudrate**: 9600 bps
- **RX**: GPIO16
- **TX**: GPIO17
- **Enable**: GPIO25

### WiFi
- **Standard**: 802.11 b/g/n
- **Fréquence**: 2.4 GHz
- **Antenne**: Intégrée PCB

## ⚡ Alimentation

### Alimentation Principale
- **Entrée**: 230V AC
- **Sortie**: 5V DC / 2A
- **Protection**: Fusible + varistance

### Alimentation ESP32
- **Entrée**: 5V DC (via USB ou VIN)
- **Régulateur**: 3.3V intégré
- **Consommation**: ~240mA (WiFi actif)

## 🔧 Schéma de Câblage

\`\`\`
230V AC ──┬── Fusible 10A ── Contacteur Principal ── Connecteur Type 2
          │
          ├── Transformateur 230V/5V ── ESP32 VIN
          │
          ├── Capteur Tension ── GPIO32
          │
          └── Capteur Courant L1 ── GPIO34
              Capteur Courant L2 ── GPIO35

Relais Contacteur ── GPIO19 ── Transistor ── 5V
Relais Lock ── GPIO21 ── Transistor ── 5V
Relais Pilot ── GPIO22 ── Transistor ── 5V

LEDs ── Résistances 220Ω ── GPIO2,4,5,18
Boutons ── Pull-up 10kΩ ── GPIO12,13,14
Buzzer ── GPIO26
\`\`\`

## 🧪 Tests de Validation

### Test d'Initialisation
\`\`\`cpp
bool hardwareTest() {
    // Test LEDs
    testLEDs();
    
    // Test relais
    testRelays();
    
    // Test capteurs
    testSensors();
    
    // Test boutons
    testButtons();
    
    return true;
}
\`\`\`

### Test des Capteurs
\`\`\`cpp
void testSensors() {
    float current1 = readCurrent1();
    float current2 = readCurrent2();
    float voltage = readVoltage();
    float temperature = readTemperature();
    
    // Validation des plages
    assert(current1 >= 0 && current1 <= 30);
    assert(voltage >= 0 && voltage <= 250);
    assert(temperature >= -20 && temperature <= 80);
}
\`\`\`

## 📋 Checklist de Validation

- [ ] Toutes les LEDs s'allument et s'éteignent
- [ ] Tous les relais s'activent et se désactivent
- [ ] Les capteurs ADC donnent des valeurs cohérentes
- [ ] Les boutons sont détectés correctement
- [ ] Le buzzer fonctionne
- [ ] La communication RFID est établie
- [ ] Les seuils de sécurité sont respectés
- [ ] L'arrêt d'urgence fonctionne
- [ ] Le WiFi se connecte correctement

## 🔗 Références

- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [DOIT ESP32 DevKit Pinout](https://github.com/SmartArduino/SZDOITWiKi/wiki/ESP8266---ESP32)
