/**
* @file power_manager.cpp
* @brief Implémentation du gestionnaire d'alimentation ESP32
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
*/

#include "power_manager.h"
#include "esp_pm.h"
#include "esp_sleep.h"
#include "esp_wifi.h"
#include "esp_bt.h"
#include "driver/adc.h"
#include "soc/rtc.h"

PowerManager::PowerManager() {
   currentMode = POWER_MODE_ACTIVE;
   currentState = POWER_STATE_NORMAL;
   ecoModeEnabled = false;
   autoCpuFrequency = false;
   autoAlerts = true;
   
   lastMeasurementTime = 0;
   startTime = 0;
   totalEnergyConsumed = 0;
   measurementCount = 0;
   
   lowVoltageCallback = nullptr;
   overheatCallback = nullptr;
   
   // Seuils par défaut
   voltageThresholdLow = 4.5;      // 4.5V
   voltageThresholdCritical = 4.0;  // 4.0V
   temperatureThresholdHigh = 75.0; // 75°C
   
   memset(&lastMeasurements, 0, sizeof(power_measurements_t));
}

PowerManager::~PowerManager() {
   // Restaurer l'alimentation normale avant destruction
   setMode(POWER_MODE_ACTIVE);
   powerUpAll();
}

bool PowerManager::init() {
    Serial.println("🔋 Initialisation du gestionnaire d'alimentation...");
    
    startTime = millis();
    
    // Configuration de la gestion d'alimentation ESP32 (version compatible)
    #ifdef CONFIG_PM_ENABLE
    esp_pm_config_esp32_t pm_config;
    pm_config.max_freq_mhz = 240;
    pm_config.min_freq_mhz = 80;
    pm_config.light_sleep_enable = true;
    
    esp_err_t ret = esp_pm_configure(&pm_config);
    if (ret != ESP_OK) {
        Serial.printf("⚠️ Configuration PM non supportée: %s (continuons sans PM)\n", esp_err_to_name(ret));
        // Continuer sans la gestion d'alimentation avancée
    } else {
        Serial.println("✅ Configuration PM activée");
    }
    #else
    Serial.println("ℹ️ Gestion d'alimentation ESP32 non disponible (continuons en mode simple)");
    #endif
    
    // Configuration des domaines d'alimentation
    configurePowerDomains();
    
    // Première mesure
    updateMeasurements();
    
    Serial.println("✅ Gestionnaire d'alimentation initialisé");
    return true;
}

void PowerManager::loop() {
   unsigned long now = millis();
   
   // Mise à jour des mesures toutes les 5 secondes
   if (now - lastMeasurementTime >= 5000) {
       updateMeasurements();
       lastMeasurementTime = now;
       
       // Vérification des seuils si alertes automatiques activées
       if (autoAlerts) {
           checkThresholds();
       }
       
       // Optimisation automatique si mode éco activé
       if (ecoModeEnabled) {
           optimizePowerConsumption();
       }
   }
}

power_state_t PowerManager::getState() {
   return currentState;
}

power_mode_t PowerManager::getMode() {
   return currentMode;
}

// ============================================================================
// GESTION DES MODES DE CONSOMMATION
// ============================================================================

bool PowerManager::setMode(power_mode_t mode) {
   if (mode == currentMode) {
       return true;
   }
   
   Serial.printf("🔋 Changement mode alimentation: %d -> %d\n", currentMode, mode);
   
   switch (mode) {
       case POWER_MODE_ACTIVE:
           setCpuFrequency(240);
           setWifiPower(true);
           powerUpAll();
           break;
           
       case POWER_MODE_LIGHT_SLEEP:
           setCpuFrequency(160);
           // WiFi maintenu mais optimisé
           break;
           
       case POWER_MODE_DEEP_SLEEP:
           powerDownNonEssential();
           setWifiPower(false);
           setCpuFrequency(80);
           break;
           
       case POWER_MODE_EMERGENCY:
           powerDownNonEssential();
           setWifiPower(false);
           setCpuFrequency(80);
           break;
           
       default:
           Serial.println("❌ Mode d'alimentation invalide");
           return false;
   }
   
   currentMode = mode;
   return true;
}

void PowerManager::setEcoMode(bool enable) {
   ecoModeEnabled = enable;
   Serial.printf("🔋 Mode économie: %s\n", enable ? "ACTIVÉ" : "DÉSACTIVÉ");
   
   if (enable) {
       // Optimisations immédiates
       optimizePowerConsumption();
   } else {
       // Restaurer les performances
       setMode(POWER_MODE_ACTIVE);
   }
}

void PowerManager::lightSleep(uint32_t duration_ms) {
   Serial.printf("😴 Entrée en veille légère (%lu ms)\n", duration_ms);
   
   if (duration_ms > 0) {
       esp_sleep_enable_timer_wakeup(duration_ms * 1000); // Conversion en µs
   }
   
   esp_light_sleep_start();
   
   Serial.println("🌅 Réveil de la veille légère");
}

void PowerManager::deepSleep(uint32_t duration_ms) {
   Serial.printf("💤 Entrée en veille profonde (%lu ms)\n", duration_ms);
   
   // Sauvegarder l'état avant veille profonde
   powerDownNonEssential();
   
   esp_sleep_enable_timer_wakeup(duration_ms * 1000); // Conversion en µs
   esp_deep_sleep_start();
   
   // Cette ligne ne sera jamais atteinte (réveil = reset)
}

void PowerManager::setWakeupPin(uint8_t pin, uint8_t level) {
   esp_sleep_enable_ext0_wakeup((gpio_num_t)pin, level);
   Serial.printf("🔋 Pin de réveil configuré: GPIO%d (niveau %d)\n", pin, level);
}

// ============================================================================
// GESTION DE LA FRÉQUENCE CPU
// ============================================================================

bool PowerManager::setCpuFrequency(uint32_t frequency_mhz) {
   // Vérifier que la fréquence est supportée
   if (frequency_mhz != 80 && frequency_mhz != 160 && frequency_mhz != 240) {
       Serial.printf("❌ Fréquence CPU non supportée: %lu MHz\n", frequency_mhz);
       return false;
   }
   
   bool success = setCpuFrequencyMhz(frequency_mhz);
   
   if (success) {
       Serial.printf("🔋 Fréquence CPU: %lu MHz\n", frequency_mhz);
   } else {
       Serial.printf("❌ Erreur changement fréquence CPU: %lu MHz\n", frequency_mhz);
   }
   
   return success;
}

uint32_t PowerManager::getCpuFrequency() {
   return getCpuFrequencyMhz();
}

void PowerManager::setAutoCpuFrequency(bool enable) {
   autoCpuFrequency = enable;
   Serial.printf("🔋 Fréquence CPU automatique: %s\n", enable ? "ACTIVÉE" : "DÉSACTIVÉE");
}

// ============================================================================
// SURVEILLANCE DE L'ALIMENTATION
// ============================================================================

power_measurements_t PowerManager::readMeasurements() {
   power_measurements_t measurements;
   
   measurements.input_voltage = readInputVoltage();
   measurements.input_current = readInputCurrent();
   measurements.cpu_voltage = 3.3; // Fixe pour ESP32
   measurements.battery_voltage = readBatteryVoltage();
   measurements.power_consumption = calculatePowerConsumption();
   measurements.cpu_frequency = getCpuFrequency();
   measurements.temperature = readInternalTemperature();
   measurements.cpu_load = calculateCpuLoad();
   measurements.uptime = getUptime();
   
   return measurements;
}

float PowerManager::readInputVoltage() {
   #ifndef SIMULATION_MODE
   // Lecture ADC sur pin dédié (à adapter selon le circuit)
   uint32_t adc_reading = analogRead(A0);
   float voltage = (adc_reading / 4095.0) * 3.3 * 2.0; // Diviseur de tension
   return voltage;
   #else
   // Simulation: tension stable autour de 5V
   return 4.8 + (random(-20, 20) / 100.0);
   #endif
}

float PowerManager::readInputCurrent() {
   #ifndef SIMULATION_MODE
   // Lecture via capteur de courant (ex: INA219)
   // À implémenter selon le capteur utilisé
   return 250.0; // mA par défaut
   #else
   // Simulation: courant variable selon la charge
   float baseCurrent = 200.0; // mA
   float cpuLoad = calculateCpuLoad();
   return baseCurrent + (cpuLoad * 2.0); // +2mA par % de charge CPU
   #endif
}

float PowerManager::readBatteryVoltage() {
   #ifndef SIMULATION_MODE
   // Si batterie de backup présente
   return 0.0; // Pas de batterie par défaut
   #else
   // Simulation: pas de batterie
   return 0.0;
   #endif
}

float PowerManager::calculatePowerConsumption() {
   float voltage = readInputVoltage();
   float current = readInputCurrent();
   return voltage * current; // mW
}

// ============================================================================
// GESTION DES PÉRIPHÉRIQUES
// ============================================================================

void PowerManager::setPeripheralPower(const char* peripheral, bool enable) {
   Serial.printf("🔋 Périphérique %s: %s\n", peripheral, enable ? "ON" : "OFF");
   
   // À implémenter selon les périphériques spécifiques
   // Exemple: contrôle via GPIO ou registres
}

void PowerManager::setWifiPower(bool enable) {
    esp_err_t ret;
    if (enable) {
        ret = esp_wifi_start();
        if (ret == ESP_OK) {
            Serial.println("🔋 WiFi: ACTIVÉ");
        } else {
            Serial.printf("⚠️ WiFi start failed: %s\n", esp_err_to_name(ret));
        }
    } else {
        ret = esp_wifi_stop();
        if (ret == ESP_OK) {
            Serial.println("🔋 WiFi: DÉSACTIVÉ");
        } else {
            Serial.printf("⚠️ WiFi stop failed: %s\n", esp_err_to_name(ret));
        }
    }
}

void PowerManager::setBluetoothPower(bool enable) {
    esp_err_t ret;
    if (enable) {
        ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
        if (ret == ESP_OK) {
            Serial.println("🔋 Bluetooth: ACTIVÉ");
        } else {
            Serial.printf("⚠️ Bluetooth enable failed: %s\n", esp_err_to_name(ret));
        }
    } else {
        ret = esp_bt_controller_disable();
        if (ret == ESP_OK) {
            Serial.println("🔋 Bluetooth: DÉSACTIVÉ");
        } else {
            Serial.printf("⚠️ Bluetooth disable failed: %s\n", esp_err_to_name(ret));
        }
    }
}

void PowerManager::powerDownNonEssential() {
   Serial.println("🔋 Arrêt des périphériques non essentiels");
   
   // Désactiver les périphériques non critiques
   setBluetoothPower(false);
   setPeripheralClocks(false);
   
   // Réduire la fréquence CPU
   setCpuFrequency(80);
}

void PowerManager::powerUpAll() {
   Serial.println("🔋 Activation de tous les périphériques");
   
   // Restaurer la fréquence CPU
   setCpuFrequency(240);
   
   // Réactiver les périphériques
   setPeripheralClocks(true);
   setWifiPower(true);
}

// ============================================================================
// SURVEILLANCE ET ALERTES
// ============================================================================

bool PowerManager::checkPowerLevels() {
   float voltage = readInputVoltage();
   float temperature = readInternalTemperature();
   
   // Vérification tension
   if (voltage < voltageThresholdCritical) {
       currentState = POWER_STATE_CRITICAL;
       if (lowVoltageCallback) {
           lowVoltageCallback(voltage);
       }
       return false;
   } else if (voltage < voltageThresholdLow) {
       currentState = POWER_STATE_LOW_VOLTAGE;
   } else {
       currentState = POWER_STATE_NORMAL;
   }
   
   // Vérification température
   if (temperature > temperatureThresholdHigh) {
       if (overheatCallback) {
           overheatCallback(temperature);
       }
       return false;
   }
   
   return true;
}

void PowerManager::setLowVoltageCallback(void (*callback)(float voltage)) {
   lowVoltageCallback = callback;
}

void PowerManager::setOverheatCallback(void (*callback)(float temperature)) {
   overheatCallback = callback;
}

void PowerManager::setAutoAlerts(bool enable) {
   autoAlerts = enable;
   Serial.printf("🔋 Alertes automatiques: %s\n", enable ? "ACTIVÉES" : "DÉSACTIVÉES");
}

// ============================================================================
// STATISTIQUES ET DIAGNOSTIC
// ============================================================================

unsigned long PowerManager::getUptime() {
   return millis() - startTime;
}

float PowerManager::getAveragePowerConsumption() {
   if (measurementCount == 0) return 0.0;
   return totalEnergyConsumed / measurementCount;
}

uint32_t PowerManager::estimateBatteryLife(uint32_t battery_capacity_mah) {
   float avgCurrent = readInputCurrent();
   if (avgCurrent <= 0) return 0;
   
   // Estimation simple: capacité / courant moyen
   float hours = battery_capacity_mah / avgCurrent;
   return (uint32_t)(hours * 60); // Retour en minutes
}

void PowerManager::printPowerStats() {
   power_measurements_t measurements = readMeasurements();
   
   Serial.println("🔋 ===== STATISTIQUES D'ALIMENTATION =====");
   Serial.printf("   Tension d'entrée: %.2f V\n", measurements.input_voltage);
   Serial.printf("   Courant d'entrée: %.2f mA\n", measurements.input_current);
   Serial.printf("   Consommation: %.2f mW\n", measurements.power_consumption);
   Serial.printf("   Fréquence CPU: %.0f MHz\n", measurements.cpu_frequency);
   Serial.printf("   Température: %.1f °C\n", measurements.temperature);
   Serial.printf("   Charge CPU: %d %%\n", measurements.cpu_load);
   Serial.printf("   Temps de fonctionnement: %lu ms\n", measurements.uptime);
   Serial.printf("   Mode actuel: %d\n", currentMode);
   Serial.printf("   État: %d\n", currentState);
   Serial.printf("   Consommation moyenne: %.2f mW\n", getAveragePowerConsumption());
   Serial.println("🔋 ========================================");
}

void PowerManager::resetStats() {
   totalEnergyConsumed = 0;
   measurementCount = 0;
   startTime = millis();
   Serial.println("🔋 Statistiques réinitialisées");
}

// ============================================================================
// MÉTHODES PRIVÉES
// ============================================================================

void PowerManager::updateMeasurements() {
   lastMeasurements = readMeasurements();
   
   // Mise à jour des statistiques
   totalEnergyConsumed += lastMeasurements.power_consumption;
   measurementCount++;
}

void PowerManager::checkThresholds() {
   if (!checkPowerLevels()) {
       Serial.println("⚠️ Seuils d'alimentation dépassés!");
       
       if (currentState == POWER_STATE_CRITICAL) {
           // Passage automatique en mode urgence
           setMode(POWER_MODE_EMERGENCY);
       }
   }
}

void PowerManager::optimizePowerConsumption() {
   uint8_t cpuLoad = calculateCpuLoad();
   
   if (autoCpuFrequency) {
       // Ajustement automatique de la fréquence selon la charge
       if (cpuLoad < 30) {
           setCpuFrequency(80);
       } else if (cpuLoad < 70) {
           setCpuFrequency(160);
       } else {
           setCpuFrequency(240);
       }
   }
}

float PowerManager::readInternalTemperature() {
   #ifndef SIMULATION_MODE
   // Lecture du capteur de température interne ESP32
   // Note: nécessite calibration pour être précis
   return temperatureRead();
   #else
   // Simulation: température variable
   return 35.0 + (random(-50, 100) / 10.0);
   #endif
}

uint8_t PowerManager::calculateCpuLoad() {
   // Estimation simple basée sur la fréquence et l'activité
   static unsigned long lastIdleTime = 0;
   static unsigned long lastTotalTime = 0;
   
   unsigned long currentTime = millis();
   unsigned long deltaTime = currentTime - lastTotalTime;
   
   if (deltaTime < 1000) return 0; // Pas assez de temps écoulé
   
   // Estimation grossière (à améliorer avec des mesures réelles)
   uint8_t load = random(10, 80); // Simulation
   
   lastTotalTime = currentTime;
   return load;
}

void PowerManager::configurePowerDomains() {
   // Configuration des domaines d'alimentation ESP32
   // À adapter selon les besoins spécifiques
   Serial.println("🔋 Configuration des domaines d'alimentation");
}

void PowerManager::setPeripheralClocks(bool enable) {
   // Contrôle des horloges des périphériques
   // À implémenter selon les périphériques utilisés
   Serial.printf("🔋 Horloges périphériques: %s\n", enable ? "ACTIVÉES" : "DÉSACTIVÉES");
}
