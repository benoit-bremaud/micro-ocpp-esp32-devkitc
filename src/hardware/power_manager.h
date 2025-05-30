#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

/**
* @file power_manager.h
* @brief Gestionnaire de l'alimentation pour ESP32 DOIT DevKitC
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* 
* Cette classe gère l'alimentation, la consommation énergétique et les modes
* de veille pour optimiser l'autonomie et la fiabilité du système.
*/

#include <Arduino.h>
#include "hardware_config.h"

/**
* @brief Modes de consommation
*/
typedef enum {
   POWER_MODE_ACTIVE = 0,      // Mode actif normal
   POWER_MODE_LIGHT_SLEEP,     // Veille légère (WiFi maintenu)
   POWER_MODE_DEEP_SLEEP,      // Veille profonde (réveil par timer/GPIO)
   POWER_MODE_HIBERNATION,     // Hibernation (réveil par reset uniquement)
   POWER_MODE_EMERGENCY        // Mode urgence (consommation minimale)
} power_mode_t;

/**
* @brief États de l'alimentation
*/
typedef enum {
   POWER_STATE_NORMAL = 0,     // Alimentation normale
   POWER_STATE_LOW_VOLTAGE,    // Tension faible
   POWER_STATE_CRITICAL,       // Tension critique
   POWER_STATE_BATTERY,        // Sur batterie
   POWER_STATE_CHARGING,       // En charge
   POWER_STATE_FAULT           // Défaut alimentation
} power_state_t;

/**
* @brief Structure des mesures d'alimentation
*/
typedef struct {
   float input_voltage;        // Tension d'entrée (V)
   float input_current;        // Courant d'entrée (mA)
   float cpu_voltage;          // Tension CPU (V)
   float battery_voltage;      // Tension batterie (V)
   float power_consumption;    // Consommation totale (mW)
   float cpu_frequency;        // Fréquence CPU (MHz)
   float temperature;          // Température interne (°C)
   uint8_t cpu_load;          // Charge CPU (%)
   unsigned long uptime;       // Temps de fonctionnement (ms)
} power_measurements_t;

/**
* @brief Gestionnaire de l'alimentation
*/
class PowerManager {
public:
   /**
    * @brief Constructeur
    */
   PowerManager();

   /**
    * @brief Destructeur
    */
   ~PowerManager();

   /**
    * @brief Initialise le gestionnaire d'alimentation
    * @return true si succès, false sinon
    */
   bool init();

   /**
    * @brief Boucle principale de gestion de l'alimentation
    */
   void loop();

   /**
    * @brief Obtient l'état actuel de l'alimentation
    * @return État de l'alimentation
    */
   power_state_t getState();

   /**
    * @brief Obtient le mode de consommation actuel
    * @return Mode de consommation
    */
   power_mode_t getMode();

   // ========================================================================
   // GESTION DES MODES DE CONSOMMATION
   // ========================================================================

   /**
    * @brief Définit le mode de consommation
    * @param mode Mode souhaité
    * @return true si succès, false sinon
    */
   bool setMode(power_mode_t mode);

   /**
    * @brief Active le mode économie d'énergie
    * @param enable true pour activer, false pour désactiver
    */
   void setEcoMode(bool enable);

   /**
    * @brief Entre en veille légère
    * @param duration_ms Durée en millisecondes (0 = indéfini)
    */
   void lightSleep(uint32_t duration_ms = 0);

   /**
    * @brief Entre en veille profonde
    * @param duration_ms Durée en millisecondes
    */
   void deepSleep(uint32_t duration_ms);

   /**
    * @brief Configure le réveil par GPIO
    * @param pin Pin de réveil
    * @param level Niveau de réveil (HIGH/LOW)
    */
   void setWakeupPin(uint8_t pin, uint8_t level);

   // ========================================================================
   // GESTION DE LA FRÉQUENCE CPU
   // ========================================================================

   /**
    * @brief Définit la fréquence du CPU
    * @param frequency_mhz Fréquence en MHz (80, 160, 240)
    * @return true si succès, false sinon
    */
   bool setCpuFrequency(uint32_t frequency_mhz);

   /**
    * @brief Obtient la fréquence actuelle du CPU
    * @return Fréquence en MHz
    */
   uint32_t getCpuFrequency();

   /**
    * @brief Active la gestion automatique de la fréquence
    * @param enable true pour activer, false pour désactiver
    */
   void setAutoCpuFrequency(bool enable);

   // ========================================================================
   // SURVEILLANCE DE L'ALIMENTATION
   // ========================================================================

   /**
    * @brief Lit toutes les mesures d'alimentation
    * @return Structure avec toutes les mesures
    */
   power_measurements_t readMeasurements();

   /**
    * @brief Lit la tension d'entrée
    * @return Tension en volts
    */
   float readInputVoltage();

   /**
    * @brief Lit le courant d'entrée
    * @return Courant en milliampères
    */
   float readInputCurrent();

   /**
    * @brief Lit la tension de la batterie
    * @return Tension en volts
    */
   float readBatteryVoltage();

   /**
    * @brief Calcule la consommation totale
    * @return Consommation en milliwatts
    */
   float calculatePowerConsumption();

   // ========================================================================
   // GESTION DES PÉRIPHÉRIQUES
   // ========================================================================

   /**
    * @brief Active/désactive un périphérique
    * @param peripheral Nom du périphérique
    * @param enable true pour activer, false pour désactiver
    */
   void setPeripheralPower(const char* peripheral, bool enable);

   /**
    * @brief Active/désactive le WiFi
    * @param enable true pour activer, false pour désactiver
    */
   void setWifiPower(bool enable);

   /**
    * @brief Active/désactive le Bluetooth
    * @param enable true pour activer, false pour désactiver
    */
   void setBluetoothPower(bool enable);

   /**
    * @brief Coupe l'alimentation des périphériques non essentiels
    */
   void powerDownNonEssential();

   /**
    * @brief Restaure l'alimentation de tous les périphériques
    */
   void powerUpAll();

   // ========================================================================
   // SURVEILLANCE ET ALERTES
   // ========================================================================

   /**
    * @brief Vérifie les seuils d'alimentation
    * @return true si tout est OK, false sinon
    */
   bool checkPowerLevels();

   /**
    * @brief Définit un callback d'alerte de tension faible
    * @param callback Fonction de callback
    */
   void setLowVoltageCallback(void (*callback)(float voltage));

   /**
    * @brief Définit un callback d'alerte de température
    * @param callback Fonction de callback
    */
   void setOverheatCallback(void (*callback)(float temperature));

   /**
    * @brief Active/désactive les alertes automatiques
    * @param enable true pour activer, false pour désactiver
    */
   void setAutoAlerts(bool enable);

   // ========================================================================
   // STATISTIQUES ET DIAGNOSTIC
   // ========================================================================

   /**
    * @brief Obtient le temps de fonctionnement
    * @return Temps en millisecondes
    */
   unsigned long getUptime();

   /**
    * @brief Obtient la consommation moyenne
    * @return Consommation moyenne en mW
    */
   float getAveragePowerConsumption();

   /**
    * @brief Estime l'autonomie restante
    * @param battery_capacity_mah Capacité de la batterie en mAh
    * @return Autonomie estimée en minutes
    */
   uint32_t estimateBatteryLife(uint32_t battery_capacity_mah);

   /**
    * @brief Affiche les statistiques d'alimentation
    */
   void printPowerStats();

   /**
    * @brief Réinitialise les statistiques
    */
   void resetStats();

private:
   // Variables d'état
   power_mode_t currentMode;
   power_state_t currentState;
   bool ecoModeEnabled;
   bool autoCpuFrequency;
   bool autoAlerts;
   
   // Mesures et statistiques
   power_measurements_t lastMeasurements;
   unsigned long lastMeasurementTime;
   unsigned long startTime;
   float totalEnergyConsumed;
   uint32_t measurementCount;
   
   // Callbacks
   void (*lowVoltageCallback)(float voltage);
   void (*overheatCallback)(float temperature);
   
   // Seuils
   float voltageThresholdLow;
   float voltageThresholdCritical;
   float temperatureThresholdHigh;
   
   // Méthodes privées
   void updateMeasurements();
   void checkThresholds();
   void optimizePowerConsumption();
   float readInternalTemperature();
   uint8_t calculateCpuLoad();
   void configurePowerDomains();
   void setPeripheralClocks(bool enable);
};

#endif // POWER_MANAGER_H
