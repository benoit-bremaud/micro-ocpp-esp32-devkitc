# Intégration MicroOCPP

## 📋 À propos de MicroOCPP

[MicroOCPP](https://github.com/matth-x/MicroOcpp) est une bibliothèque OCPP 1.6 / 2.0.1 pour microcontrôleurs développée par Matthias Akstaller (matth-x). Cette bibliothèque offre une implémentation complète du protocole OCPP optimisée pour les environnements contraints comme l'ESP32.

## 🔧 Caractéristiques

- Support OCPP 1.6 et 2.0.1
- Optimisé pour les microcontrôleurs (ESP32, Arduino)
- Gestion efficace de la mémoire
- Support des Feature Profiles OCPP
- Licence MIT

## 📦 Installation

MicroOCPP est installé comme dépendance PlatformIO dans notre projet :

\`\`\`ini
lib_deps = 
    matth-x/MicroOcpp@^2.0.1
\`\`\`

## 🏗️ Architecture d'Intégration

Notre projet utilise MicroOCPP comme bibliothèque de base et ajoute des couches d'abstraction et d'extension :

\`\`\`
┌─────────────────────────────────────────┐
│           Notre Application             │
│     (Extensions et Personnalisations)   │
├─────────────────────────────────────────┤
│           Couche Hardware               │
│     (Intégration ESP32 spécifique)      │
├─────────────────────────────────────────┤
│              MicroOCPP                  │
│     (Bibliothèque OCPP de base)         │
├─────────────────────────────────────────┤
│           Arduino/ESP32                 │
│     (Framework de base)                 │
└─────────────────────────────────────────┘
\`\`\`

## 🚀 Utilisation de Base

Voici un exemple minimal d'utilisation de MicroOCPP dans notre projet :

\`\`\`cpp
#include <Arduino.h>
#include <WiFi.h>
#include <MicroOcpp.h>

void setup() {
    Serial.begin(115200);
    
    // Connexion WiFi
    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    
    // Initialisation MicroOCPP
    mocpp_initialize(
        WiFiClient(),                   // Client WiFi
        "ws://server.com:8080/ocpp",    // URL du serveur OCPP
        "CP001",                        // ID du point de charge
        "ESP32-CP",                     // Modèle
        "v1.0.0"                        // Version firmware
    );
    
    // Configuration des callbacks
    setOnBootNotificationRequest([]() {
        return true;
    });
}

void loop() {
    // Boucle principale MicroOCPP
    mocpp_loop();
    
    delay(10);
}
\`\`\`

## 📚 Documentation MicroOCPP

- [GitHub Repository](https://github.com/matth-x/MicroOcpp)
- [Wiki](https://github.com/matth-x/MicroOcpp/wiki)
- [Exemples](https://github.com/matth-x/MicroOcpp/tree/master/examples)

## 🔄 Feature Profiles Supportés

MicroOCPP supporte les Feature Profiles OCPP 1.6 suivants :

- **Core Profile** - Fonctionnalités de base
- **Smart Charging** - Gestion intelligente de la charge
- **Local Auth List** - Gestion des listes d'autorisation locales
- **Firmware Management** - Gestion des mises à jour firmware
- **Reservation** - Système de réservation

## 🛠️ Extensions Prévues

Notre projet étend MicroOCPP avec :

1. **Intégration Hardware ESP32** - Gestion des GPIO, LEDs, capteurs
2. **Interface Utilisateur** - Affichage OLED, boutons
3. **Monitoring Avancé** - Surveillance de la consommation, température
4. **Customisations OCPP** - Extensions spécifiques à nos besoins

## ⚠️ Limitations Connues

- MicroOCPP a des limitations de mémoire sur certains microcontrôleurs
- Certaines fonctionnalités avancées d'OCPP peuvent nécessiter des extensions
- La documentation peut être limitée pour certaines fonctionnalités

## 🔗 Liens Utiles

- [OCPP 1.6 Specification](https://www.openchargealliance.org/protocols/ocpp-16/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [PlatformIO](https://platformio.org/)
