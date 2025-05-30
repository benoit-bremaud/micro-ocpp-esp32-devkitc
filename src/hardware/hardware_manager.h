#ifndef HARDWARE_MANAGER_H
#define HARDWARE_MANAGER_H

/**
* @file hardware_manager.h
* @brief Gestionnaire du matériel pour ESP32 DOIT DevKitC
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* 
* Cette classe gère tous les aspects matériels de l'ESP32 :
* - Configuration des GPIO
* - Lecture des capteurs (courant, tension, température)
* - Contrôle des LEDs et du buzzer
* - Surveillance de l'état du système
*/

#include <Arduino.h>
#include "hardware_config.h"

/**
* @brief États du gestionnaire hardware
*/
typedef enum {
   HW_STATE_INIT = 0,          // Initialisation
   HW_STATE_READY,             // Prêt
   HW_STATE_CHARGING,          // En charge
   HW_STATE_ERROR,             // Erreur
   HW_STATE_MAINTENANCE,       // Maintenance
   HW_STATE_OFFLINE           // Hors ligne
} hardware_state_t;

/**
* @brief Structure des mesures hardware
*/
typedef struct {
   unsigned long timestamp;    // Timestamp de la mesure
   float current_l1;          // Courant phase L1 (A)
   float current_l2;          // Courant phase L2 (A)
   float voltage;             // Tension (V)
   float temperature;         // Température (°C)
   float power;               // Puissance totale (kW)
   float energy;              // Énergie cumulée (kWh)
   bool button_pressed;       // État du bouton
} hardware_measurements_t;

/**
* @brief Gestionnaire du matériel ESP32
*/
class HardwareManager {
public:
   /**
    * @brief Constructeur
    */
   HardwareManager();

   /**
    * @brief Destructeur
    */
   ~HardwareManager();

   /**
    * @brief Initialise le gestionnaire hardware
    * @return true si succès, false sinon
    */
   bool init();

   /**
    * @brief Boucle principale du gestionnaire
    */
   void loop();

   /**
    * @brief Obtient l'état actuel du hardware
    * @return État du hardware
    */
   hardware_state_t getState();

   // ========================================================================
   // CONTRÔLE DES LEDs
   // ========================================================================

   /**
    * @brief Contrôle la LED de statut
    * @param state true pour allumer, false pour éteindre
    */
   void setStatusLed(bool state);

   /**
    * @brief Contrôle la LED d'erreur
    * @param state true pour allumer, false pour éteindre
    */
   void setErrorLed(bool state);

   /**
    * @brief Fait clignoter la LED de statut
    * @param interval_ms Intervalle de clignotement en ms
    */
   void blinkStatusLed(uint32_t interval_ms);

   /**
    * @brief Fait clignoter la LED d'erreur
    * @param interval_ms Intervalle de clignotement en ms
    */
   void blinkErrorLed(uint32_t interval_ms);

   /**
    * @brief Arrête le clignotement des LEDs
    */
   void stopBlinking();

   // ========================================================================
   // CONTRÔLE DU BUZZER
   // ========================================================================

   /**
    * @brief Active le buzzer pendant une durée
    * @param duration_ms Durée en millisecondes
    */
   void buzzer(uint32_t duration_ms);

   /**
    * @brief Fait biper le buzzer plusieurs fois
    * @param count Nombre de bips
    * @param duration_ms Durée de chaque bip
    */
   void buzzerBeep(uint8_t count, uint32_t duration_ms = 100);

   /**
    * @brief Pattern sonore d'alerte
    */
   void buzzerAlert();

   // ========================================================================
   // LECTURE DES CAPTEURS
   // ========================================================================

   /**
    * @brief Lit toutes les mesures hardware
    * @return Structure avec toutes les mesures
    */
   hardware_measurements_t readMeasurements();

   /**
    * @brief Lit le courant d'une phase
    * @param phase Numéro de phase (1 ou 2)
    * @return Courant en ampères
    */
   float readCurrent(uint8_t phase);

   /**
    * @brief Lit la tension
    * @return Tension en volts
    */
   float readVoltage();

   /**
    * @brief Lit la température
    * @return Température en degrés Celsius
    */
   float readTemperature();

   /**
    * @brief Calcule la puissance totale
    * @return Puissance en kilowatts
    */
   float calculatePower();

   /**
    * @brief Vérifie l'état du bouton
    * @return true si pressé, false sinon
    */
   bool isButtonPressed();

   // ========================================================================
   // DIAGNOSTIC ET TESTS
   // ========================================================================

   /**
    * @brief Lance l'auto-test du hardware
    * @return true si tous les tests passent
    */
   bool runSelfTest();

   /**
    * @brief Teste les LEDs
    * @return true si test réussi
    */
   bool testLeds();

   /**
    * @brief Teste le buzzer
    * @return true si test réussi
    */
   bool testBuzzer();

   /**
    * @brief Teste les capteurs ADC
    * @return true si test réussi
    */
   bool testSensors();

   /**
    * @brief Affiche les informations de diagnostic
    */
   void printDiagnostics();

private:
   // Variables d'état
   hardware_state_t currentState;
   hardware_measurements_t lastMeasurements;
   unsigned long lastMeasurementTime;
   
   // Variables de clignotement
   unsigned long lastBlinkTime;
   unsigned long lastErrorBlinkTime;
   uint32_t blinkInterval;
   uint32_t errorBlinkInterval;
   bool statusLedState;
   bool errorLedState;
   bool blinkingEnabled;
   bool errorBlinkingEnabled;
   
   // Méthodes privées
   void updateMeasurements();
   void checkButton();
   void handleStateChange();
   bool initializeGPIO();
   bool initializeSensors();
};

#endif // HARDWARE_MANAGER_H
