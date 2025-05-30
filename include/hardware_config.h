#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

/**
* @file hardware_config.h
* @brief Configuration matérielle pour ESP32 DOIT DevKitC v1
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* 
* Définit tous les pins GPIO et constantes hardware
*/

#include <Arduino.h>

// ============================================================================
// INFORMATIONS DE LA CARTE
// ============================================================================

#define BOARD_NAME "ESP32 DOIT DevKitC"
#define BOARD_VERSION "v1"
#define HARDWARE_VERSION "1.0.0"

// ============================================================================
// CONFIGURATION DES PINS GPIO
// ============================================================================

// LEDs de statut
#define LED_STATUS_PIN      2       // LED bleue intégrée (GPIO2)
#define LED_ERROR_PIN       4       // LED rouge d'erreur (GPIO4)

// Buzzer/Beeper
#define BUZZER_PIN          5       // Buzzer piezo (GPIO5)

// Bouton utilisateur
#define BUTTON_PIN          0       // Bouton BOOT (GPIO0) - avec pull-up interne

// Capteurs de courant (ACS712 ou similaire)
#define CURRENT_SENSOR_L1_PIN   36  // ADC1_CH0 - Capteur courant phase L1
#define CURRENT_SENSOR_L2_PIN   39  // ADC1_CH3 - Capteur courant phase L2

// Capteur de tension (diviseur de tension)
#define VOLTAGE_SENSOR_PIN      34  // ADC1_CH6 - Capteur tension

// Capteur de température (TMP36 ou DS18B20)
#define TEMP_SENSOR_PIN         35  // ADC1_CH7 - Capteur température

// Relais de contrôle (optionnel)
#define RELAY_1_PIN             16  // Relais 1 (GPIO16)
#define RELAY_2_PIN             17  // Relais 2 (GPIO17)

// Communication série (UART)
#define SERIAL_RX_PIN           3   // RX0 (GPIO3)
#define SERIAL_TX_PIN           1   // TX0 (GPIO1)

// Communication I2C (pour écran OLED ou autres)
#define I2C_SDA_PIN             21  // SDA (GPIO21)
#define I2C_SCL_PIN             22  // SCL (GPIO22)

// Communication SPI (pour carte SD ou autres)
#define SPI_MISO_PIN            19  // MISO (GPIO19)
#define SPI_MOSI_PIN            23  // MOSI (GPIO23)
#define SPI_CLK_PIN             18  // CLK (GPIO18)
#define SPI_CS_PIN              15  // CS (GPIO15)

// ============================================================================
// CONFIGURATION DES CAPTEURS
// ============================================================================

// Capteur de courant ACS712
#define ACS712_SENSITIVITY      0.066   // V/A pour ACS712-30A
#define ACS712_ZERO_CURRENT     1.65    // Tension à courant nul (Vcc/2)
#define ACS712_MAX_CURRENT      30.0    // Courant maximum (A)

// Diviseur de tension pour mesure AC
#define VOLTAGE_DIVIDER_RATIO   100.0   // Ratio du diviseur de tension
#define VOLTAGE_MAX             250.0   // Tension maximum mesurable (V)

// Capteur de température TMP36
#define TMP36_OFFSET            0.5     // Offset en volts
#define TMP36_SCALE             100.0   // mV/°C

// ============================================================================
// CONFIGURATION ADC
// ============================================================================

#define ADC_RESOLUTION          12      // 12 bits (0-4095)
#define ADC_VREF                3.3     // Tension de référence (V)
#define ADC_SAMPLES             10      // Nombre d'échantillons pour moyennage

// ============================================================================
// CONFIGURATION SÉRIE
// ============================================================================

#define SERIAL_BAUD_RATE        115200  // Vitesse série
#define SERIAL_TIMEOUT          1000    // Timeout série (ms)

// ============================================================================
// CONFIGURATION TIMING
// ============================================================================

#define MEASUREMENT_INTERVAL    5000    // Intervalle de mesure (ms)
#define HEARTBEAT_INTERVAL      10000   // Intervalle heartbeat (ms)
#define BLINK_INTERVAL_NORMAL   1000    // Clignotement normal (ms)
#define BLINK_INTERVAL_FAST     200     // Clignotement rapide (ms)
#define BLINK_INTERVAL_ERROR    100     // Clignotement erreur (ms)

// ============================================================================
// SEUILS ET LIMITES
// ============================================================================

// Seuils de courant
#define CURRENT_THRESHOLD_LOW   0.1     // Seuil bas courant (A)
#define CURRENT_THRESHOLD_HIGH  25.0    // Seuil haut courant (A)

// Seuils de tension
#define VOLTAGE_THRESHOLD_LOW   200.0   // Seuil bas tension (V)
#define VOLTAGE_THRESHOLD_HIGH  250.0   // Seuil haut tension (V)

// Seuils de température
#define TEMP_THRESHOLD_LOW      -10.0   // Seuil bas température (°C)
#define TEMP_THRESHOLD_HIGH     60.0    // Seuil haut température (°C)

// ============================================================================
// CONFIGURATION WATCHDOG
// ============================================================================

#define WATCHDOG_TIMEOUT_MAIN   30000   // Timeout watchdog principal (ms)
#define WATCHDOG_TIMEOUT_COMM   60000   // Timeout watchdog communication (ms)
#define WATCHDOG_TIMEOUT_TASK   10000   // Timeout watchdog tâche (ms)

// ============================================================================
// CONFIGURATION POWER MANAGEMENT
// ============================================================================

#define CPU_FREQ_MAX            240     // Fréquence CPU max (MHz)
#define CPU_FREQ_NORMAL         160     // Fréquence CPU normale (MHz)
#define CPU_FREQ_ECO            80      // Fréquence CPU économique (MHz)

// ============================================================================
// MACROS UTILITAIRES
// ============================================================================

// Conversion ADC vers tension
#define ADC_TO_VOLTAGE(adc_val) ((adc_val) * ADC_VREF / 4095.0)

// Conversion tension vers courant (ACS712)
#define VOLTAGE_TO_CURRENT(voltage) (((voltage) - ACS712_ZERO_CURRENT) / ACS712_SENSITIVITY)

// Conversion tension vers température (TMP36)
#define VOLTAGE_TO_TEMP(voltage) (((voltage) - TMP36_OFFSET) * TMP36_SCALE)

// Vérification des limites
#define IS_CURRENT_VALID(current) ((current) >= 0 && (current) <= ACS712_MAX_CURRENT)
#define IS_VOLTAGE_VALID(voltage) ((voltage) >= 0 && (voltage) <= VOLTAGE_MAX)
#define IS_TEMP_VALID(temp) ((temp) >= TEMP_THRESHOLD_LOW && (temp) <= TEMP_THRESHOLD_HIGH)

// ============================================================================
// MODES DE FONCTIONNEMENT
// ============================================================================

// Mode simulation (défini dans platformio.ini)
#ifdef SIMULATION_MODE
    #define SIM_CURRENT_BASE    10.0    // Courant de base simulation (A)
    #define SIM_VOLTAGE_BASE    230.0   // Tension de base simulation (V)
    #define SIM_TEMP_BASE       25.0    // Température de base simulation (°C)
    #define SIM_VARIATION       0.1     // Variation simulation (facteur)
#endif

// ============================================================================
// VALIDATION DES PINS
// ============================================================================

// Vérifier que les pins ADC sont valides
#if CURRENT_SENSOR_L1_PIN < 32 || CURRENT_SENSOR_L1_PIN > 39
    #error "CURRENT_SENSOR_L1_PIN doit être un pin ADC1 (32-39)"
#endif

#if CURRENT_SENSOR_L2_PIN < 32 || CURRENT_SENSOR_L2_PIN > 39
    #error "CURRENT_SENSOR_L2_PIN doit être un pin ADC1 (32-39)"
#endif

#if VOLTAGE_SENSOR_PIN < 32 || VOLTAGE_SENSOR_PIN > 39
    #error "VOLTAGE_SENSOR_PIN doit être un pin ADC1 (32-39)"
#endif

#if TEMP_SENSOR_PIN < 32 || TEMP_SENSOR_PIN > 39
    #error "TEMP_SENSOR_PIN doit être un pin ADC1 (32-39)"
#endif

// ============================================================================
// FONCTIONS UTILITAIRES INLINE
// ============================================================================

/**
 * @brief Lit une valeur ADC avec moyennage
 * @param pin Pin ADC à lire
 * @return Valeur ADC moyennée
 */
inline uint32_t readADCAverage(uint8_t pin) {
    uint32_t sum = 0;
    for (int i = 0; i < ADC_SAMPLES; i++) {
        sum += analogRead(pin);
        delayMicroseconds(100);
    }
    return sum / ADC_SAMPLES;
}

/**
 * @brief Convertit une valeur ADC en tension
 * @param adc_value Valeur ADC (0-4095)
 * @return Tension en volts
 */
inline float adcToVoltage(uint32_t adc_value) {
    return ADC_TO_VOLTAGE(adc_value);
}

/**
 * @brief Limite une valeur entre min et max
 * @param value Valeur à limiter
 * @param min_val Valeur minimum
 * @param max_val Valeur maximum
 * @return Valeur limitée
 */
template<typename T>
inline T constrain_value(T value, T min_val, T max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

#endif // HARDWARE_CONFIG_H
