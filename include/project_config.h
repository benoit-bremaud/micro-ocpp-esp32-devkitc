#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

/**
 * @file project_config.h
 * @brief Configuration globale du projet OCPP 1.6 avec MicroOCPP
 * 
 * Issue: [INFRA] Project Structure Setup
 * 
 * Ce fichier contient toutes les configurations globales du projet,
 * incluant les paramètres OCPP, ESP32, et les Feature Profiles supportés.
 */

// ============================================================================
// INFORMATIONS PROJET
// ============================================================================
#define PROJECT_NAME "micro-ocpp-esp32-devkitc"
#define PROJECT_VERSION "2.0.0"
#define OCPP_VERSION "1.6"

// ============================================================================
// CONFIGURATION ESP32
// ============================================================================
#define SERIAL_BAUD_RATE                115200
#define LED_STATUS_PIN                  2
#define LED_ERROR_PIN                   4
#define LED_WIFI_PIN                    5

// Configuration mémoire
#define HEAP_WARNING_THRESHOLD          30000   // Bytes

// ============================================================================
// CONFIGURATION WIFI
// ============================================================================
#define WIFI_SSID_MAX_LENGTH            32
#define WIFI_PASSWORD_MAX_LENGTH        64
#define WIFI_TIMEOUT_MS                 10000
#define WIFI_RETRY_DELAY_MS             1000
#define WIFI_MAX_RETRIES                5
#define WIFI_RECONNECT_INTERVAL_MS      30000

// ============================================================================
// CONFIGURATION OCPP
// ============================================================================
#define OCPP_HEARTBEAT_INTERVAL         300     // Secondes
#define OCPP_MESSAGE_TIMEOUT_MS         30000   // 30 secondes
#define OCPP_RECONNECT_DELAY_MS         5000    // 5 secondes

// Configuration des identifiants
#define CHARGE_POINT_ID_MAX_LENGTH      20
#define ID_TAG_MAX_LENGTH               20
#define VENDOR_ID_MAX_LENGTH            255

// ============================================================================
// CONFIGURATION MICROOCPP
// ============================================================================
#define MO_ENABLE_ALL_OPERATIONS        1       // Activer toutes les opérations
#define MO_ENABLE_SMART_CHARGING        1       // Activer Smart Charging
#define MO_ENABLE_FIRMWARE_MANAGEMENT   1       // Activer Firmware Management
#define MO_ENABLE_LOCAL_AUTH_LIST       1       // Activer Local Auth List
#define MO_ENABLE_RESERVATION           1       // Activer Reservation

// ============================================================================
// CONFIGURATION LOGGING
// ============================================================================
typedef enum {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_WARNING = 1,
    LOG_LEVEL_INFO = 2,
    LOG_LEVEL_DEBUG = 3,
    LOG_LEVEL_VERBOSE = 4
} log_level_t;

#define LOG_LEVEL                       LOG_LEVEL_INFO
#define LOG_BUFFER_SIZE                 512
#define LOG_TIMESTAMP_ENABLED           1

// ============================================================================
// CONFIGURATION CHARGE POINT
// ============================================================================
#define MAX_CONNECTORS                  2       // Nombre de connecteurs
#define CONNECTOR_ID_CHARGE_POINT       0       // ID du Charge Point
#define METER_VALUES_INTERVAL           60      // Secondes

// ============================================================================
// TIMEOUTS ET DÉLAIS
// ============================================================================
#define BOOT_NOTIFICATION_RETRY_INTERVAL 60000  // 1 minute
#define TRANSACTION_MESSAGE_RETRY_INTERVAL 30000 // 30 secondes
#define STATUS_NOTIFICATION_DEBOUNCE    1000    // 1 seconde

#endif // PROJECT_CONFIG_H
