#ifndef FEATURE_PROFILES_H
#define FEATURE_PROFILES_H

/**
 * @file feature_profiles.h
 * @brief Définitions des Feature Profiles OCPP 1.6
 * 
 * Issue: [INFRA] Project Structure Setup
 * 
 * Ce fichier définit les Feature Profiles officiels OCPP 1.6
 * et les messages associés à chaque profil.
 */

#include <Arduino.h>

// ============================================================================
// ÉNUMÉRATIONS DES FEATURE PROFILES
// ============================================================================

/**
 * @brief Feature Profiles OCPP 1.6 officiels
 */
typedef enum {
    FEATURE_PROFILE_CORE_ID = 0,
    FEATURE_PROFILE_FIRMWARE_MANAGEMENT_ID = 1,
    FEATURE_PROFILE_LOCAL_AUTH_LIST_ID = 2,
    FEATURE_PROFILE_REMOTE_TRIGGER_ID = 3,
    FEATURE_PROFILE_RESERVATION_ID = 4,
    FEATURE_PROFILE_SMART_CHARGING_ID = 5,
    FEATURE_PROFILE_COUNT = 6
} feature_profile_id_t;

/**
 * @brief Noms des Feature Profiles (pour configuration)
 */
extern const char* FEATURE_PROFILE_NAMES[FEATURE_PROFILE_COUNT];

// ============================================================================
// MESSAGES PAR FEATURE PROFILE
// ============================================================================

/**
 * @brief Messages du Core Profile
 */
typedef enum {
    // Charge Point → Central System
    CORE_MSG_AUTHORIZE = 0,
    CORE_MSG_BOOT_NOTIFICATION,
    CORE_MSG_DATA_TRANSFER_CP,
    CORE_MSG_HEARTBEAT,
    CORE_MSG_METER_VALUES,
    CORE_MSG_START_TRANSACTION,
    CORE_MSG_STATUS_NOTIFICATION,
    CORE_MSG_STOP_TRANSACTION,
    
    // Central System → Charge Point
    CORE_MSG_CHANGE_AVAILABILITY,
    CORE_MSG_CHANGE_CONFIGURATION,
    CORE_MSG_CLEAR_CACHE,
    CORE_MSG_DATA_TRANSFER_CS,
    CORE_MSG_GET_CONFIGURATION,
    CORE_MSG_REMOTE_START_TRANSACTION,
    CORE_MSG_REMOTE_STOP_TRANSACTION,
    CORE_MSG_RESET,
    CORE_MSG_UNLOCK_CONNECTOR,
    
    CORE_MSG_COUNT
} core_message_t;

/**
 * @brief Messages du FirmwareManagement Profile
 */
typedef enum {
    FIRMWARE_MSG_UPDATE_FIRMWARE = 0,
    FIRMWARE_MSG_GET_DIAGNOSTICS,
    FIRMWARE_MSG_FIRMWARE_STATUS_NOTIFICATION,
    FIRMWARE_MSG_DIAGNOSTICS_STATUS_NOTIFICATION,
    FIRMWARE_MSG_COUNT
} firmware_message_t;

/**
 * @brief Messages du LocalAuthListManagement Profile
 */
typedef enum {
    LOCAL_AUTH_MSG_GET_LOCAL_LIST_VERSION = 0,
    LOCAL_AUTH_MSG_SEND_LOCAL_LIST,
    LOCAL_AUTH_MSG_COUNT
} local_auth_message_t;

/**
 * @brief Messages du RemoteTrigger Profile
 */
typedef enum {
    REMOTE_TRIGGER_MSG_TRIGGER_MESSAGE = 0,
    REMOTE_TRIGGER_MSG_COUNT
} remote_trigger_message_t;

/**
 * @brief Messages du Reservation Profile
 */
typedef enum {
    RESERVATION_MSG_RESERVE_NOW = 0,
    RESERVATION_MSG_CANCEL_RESERVATION,
    RESERVATION_MSG_COUNT
} reservation_message_t;

/**
 * @brief Messages du SmartCharging Profile
 */
typedef enum {
    SMART_CHARGING_MSG_SET_CHARGING_PROFILE = 0,
    SMART_CHARGING_MSG_CLEAR_CHARGING_PROFILE,
    SMART_CHARGING_MSG_GET_COMPOSITE_SCHEDULE,
    SMART_CHARGING_MSG_COUNT
} smart_charging_message_t;

// ============================================================================
// STRUCTURES DE CONFIGURATION
// ============================================================================

/**
 * @brief Configuration d'un Feature Profile
 */
typedef struct {
    feature_profile_id_t id;
    const char* name;
    bool enabled;
    uint8_t message_count;
    const char** message_names;
} feature_profile_config_t;

/**
 * @brief Configuration globale des Feature Profiles
 */
typedef struct {
    feature_profile_config_t profiles[FEATURE_PROFILE_COUNT];
    uint8_t enabled_count;
} feature_profiles_config_t;

// ============================================================================
// FONCTIONS PUBLIQUES
// ============================================================================

/**
 * @brief Initialise la configuration des Feature Profiles
 * @return Configuration initialisée
 */
feature_profiles_config_t* FeatureProfiles_init();

/**
 * @brief Vérifie si un Feature Profile est activé
 * @param profile_id ID du Feature Profile
 * @return true si activé, false sinon
 */
bool FeatureProfiles_isEnabled(feature_profile_id_t profile_id);

/**
 * @brief Active ou désactive un Feature Profile
 * @param profile_id ID du Feature Profile
 * @param enabled État souhaité
 * @return true si succès, false sinon
 */
bool FeatureProfiles_setEnabled(feature_profile_id_t profile_id, bool enabled);

/**
 * @brief Obtient la liste des Feature Profiles activés
 * @param buffer Buffer pour stocker la liste (format CSV)
 * @param buffer_size Taille du buffer
 * @return Nombre de caractères écrits
 */
size_t FeatureProfiles_getSupportedList(char* buffer, size_t buffer_size);

/**
 * @brief Obtient le nom d'un Feature Profile
 * @param profile_id ID du Feature Profile
 * @return Nom du Feature Profile ou NULL si invalide
 */
const char* FeatureProfiles_getName(feature_profile_id_t profile_id);

/**
 * @brief Valide qu'un message appartient à un Feature Profile activé
 * @param message_name Nom du message OCPP
 * @return true si valide, false sinon
 */
bool FeatureProfiles_validateMessage(const char* message_name);

#endif // FEATURE_PROFILES_H
