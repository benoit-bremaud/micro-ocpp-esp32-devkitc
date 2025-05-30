#ifndef OCPP_CONFIG_H
#define OCPP_CONFIG_H

/**
 * @file ocpp_config.h
 * @brief Configuration globale du projet OCPP 1.6
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
#define OCPP_EDITION "2"

// ============================================================================
// FEATURE PROFILES SUPPORTÉS
// ============================================================================
#define FEATURE_PROFILE_CORE                    1  // Obligatoire
#define FEATURE_PROFILE_FIRMWARE_MANAGEMENT     1  // Optionnel
#define FEATURE_PROFILE_LOCAL_AUTH_LIST         1  // Optionnel
#define FEATURE_PROFILE_REMOTE_TRIGGER          1  // Optionnel
#define FEATURE_PROFILE_RESERVATION             1  // Optionnel
#define FEATURE_PROFILE_SMART_CHARGING          1  // Optionnel

// ============================================================================
// CONFIGURATION ESP32
// ============================================================================
#define SERIAL_BAUD_RATE                115200
#define LED_STATUS_PIN                  2
#define LED_ERROR_PIN                   4
#define LED_WIFI_PIN                    5

// Configuration mémoire
#define HEAP_WARNING_THRESHOLD          30000   // Bytes
#define STACK_SIZE_DEFAULT              8192    // Bytes

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
#define OCPP_MAX_MESSAGE_SIZE           2048    // Bytes
#define OCPP_MESSAGE_QUEUE_SIZE         10      // Nombre de messages

// Configuration des identifiants
#define CHARGE_POINT_ID_MAX_LENGTH      20
#define ID_TAG_MAX_LENGTH               20
#define VENDOR_ID_MAX_LENGTH            255

// ============================================================================
// CONFIGURATION WEBSOCKET
// ============================================================================
#define WEBSOCKET_RECONNECT_INTERVAL    5000    // ms
#define WEBSOCKET_PING_INTERVAL         30000   // ms
#define WEBSOCKET_PONG_TIMEOUT          5000    // ms
#define WEBSOCKET_MAX_RECONNECT_ATTEMPTS 10

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
// CONFIGURATION STOCKAGE
// ============================================================================
#define STORAGE_PARTITION_SIZE          1048576  // 1MB
#define STORAGE_MAX_FILES               100
#define STORAGE_CONFIG_FILE             "/config.json"
#define STORAGE_AUTH_CACHE_FILE         "/auth_cache.json"
#define STORAGE_TRANSACTION_FILE        "/transactions.json"

// ============================================================================
// CONFIGURATION CHARGE POINT
// ============================================================================
#define MAX_CONNECTORS                  2       // Nombre de connecteurs
#define CONNECTOR_ID_CHARGE_POINT       0       // ID du Charge Point
#define METER_VALUES_INTERVAL           60      // Secondes
#define CLOCK_ALIGNED_DATA_INTERVAL     900     // 15 minutes

// ============================================================================
// CONFIGURATION SMART CHARGING
// ============================================================================
#define MAX_CHARGING_PROFILES           10
#define MAX_SCHEDULE_PERIODS            24      // 24h avec périodes d'1h
#define CHARGING_RATE_UNIT_DEFAULT      "A"     // Ampères par défaut

// ============================================================================
// TIMEOUTS ET DÉLAIS
// ============================================================================
#define BOOT_NOTIFICATION_RETRY_INTERVAL 60000  // 1 minute
#define TRANSACTION_MESSAGE_RETRY_INTERVAL 30000 // 30 secondes
#define STATUS_NOTIFICATION_DEBOUNCE    1000    // 1 seconde

// ============================================================================
// CONFIGURATION DEBUG
// ============================================================================
#ifdef DEBUG
    #define DEBUG_WEBSOCKET             1
    #define DEBUG_JSON                  1
    #define DEBUG_MEMORY                1
    #define DEBUG_TIMING                1
#else
    #define DEBUG_WEBSOCKET             0
    #define DEBUG_JSON                  0
    #define DEBUG_MEMORY                0
    #define DEBUG_TIMING                0
#endif

// ============================================================================
// VALIDATION DES CONFIGURATIONS
// ============================================================================
#if OCPP_MAX_MESSAGE_SIZE < 1024
    #error "OCPP_MAX_MESSAGE_SIZE doit être au moins 1024 bytes"
#endif

#if MAX_CONNECTORS < 1 || MAX_CONNECTORS > 10
    #error "MAX_CONNECTORS doit être entre 1 et 10"
#endif

#if !FEATURE_PROFILE_CORE
    #error "Le Feature Profile Core est obligatoire"
#endif

#endif // OCPP_CONFIG_H
