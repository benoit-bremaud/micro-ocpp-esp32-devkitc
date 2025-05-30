#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

/**
 * @file hardware_config.h
 * @brief Configuration hardware pour ESP32
 * 
 * Issue: [INFRA] Project Structure Setup
 * 
 * Ce fichier contient les configurations spécifiques au hardware ESP32
 * utilisé dans le projet OCPP.
 */

#include <Arduino.h>

// ============================================================================
// CONFIGURATION GPIO
// ============================================================================

// LEDs
#define PIN_LED_STATUS                  2       // LED de statut (bleue)
#define PIN_LED_ERROR                   4       // LED d'erreur (rouge)
#define PIN_LED_WIFI                    5       // LED WiFi (verte)

// Entrées
#define PIN_BUTTON_RESET                13      // Bouton de reset
#define PIN_BUTTON_START                14      // Bouton de démarrage
#define PIN_RFID_RX                     16      // RFID RX
#define PIN_RFID_TX                     17      // RFID TX

// Sorties
#define PIN_RELAY_CONTACTOR             18      // Relais contacteur
#define PIN_RELAY_LOCK                  19      // Relais verrouillage

// Capteurs
#define PIN_CURRENT_SENSOR              34      // Capteur de courant (ADC)
#define PIN_VOLTAGE_SENSOR              35      // Capteur de tension (ADC)
#define PIN_TEMPERATURE                 32      // Capteur de température

// ============================================================================
// CONFIGURATION ADC
// ============================================================================
#define ADC_RESOLUTION                  12      // Résolution ADC (bits)
#define ADC_VREF                        3.3     // Tension de référence (V)
#define ADC_SAMPLES                     10      // Nombre d'échantillons pour moyenne

// Calibration capteurs
#define CURRENT_SENSOR_SENSITIVITY      0.066   // V/A
#define CURRENT_SENSOR_OFFSET           2.5     // V
#define VOLTAGE_SENSOR_RATIO            0.0178  // V/V

// ============================================================================
// CONFIGURATION CONNECTEURS
// ============================================================================
#define CONNECTOR_COUNT                 1       // Nombre de connecteurs physiques
#define CONNECTOR_MAX_CURRENT           32      // Courant max (A)
#define CONNECTOR_VOLTAGE               230     // Tension nominale (V)
#define CONNECTOR_PHASES                1       // Nombre de phases

// ============================================================================
// CONFIGURATION RFID
// ============================================================================
#define RFID_BAUDRATE                   9600    // Vitesse RFID
#define RFID_BUFFER_SIZE                16      // Taille buffer RFID

// ============================================================================
// CONFIGURATION WATCHDOG
// ============================================================================
#define WATCHDOG_TIMEOUT                30000   // Timeout watchdog (ms)
#define TASK_STACK_SIZE                 4096    // Taille stack tâches (bytes)
#define TASK_PRIORITY                   1       // Priorité tâches

#endif // HARDWARE_CONFIG_H
