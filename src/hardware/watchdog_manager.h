#ifndef WATCHDOG_MANAGER_H
#define WATCHDOG_MANAGER_H

/**
* @file watchdog_manager.h
* @brief Gestionnaire de surveillance (Watchdog) pour ESP32 DOIT DevKitC
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* 
* Version simplifiée compatible avec toutes les versions d'ESP-IDF
*/

#include <Arduino.h>
#include "esp_system.h"
#include "hardware_config.h"

// Inclure le watchdog de tâche seulement si disponible
#ifdef CONFIG_ESP_TASK_WDT_EN
#include "esp_task_wdt.h"
#endif

/**
* @brief Types de watchdog
*/
typedef enum {
   WDT_TYPE_TASK = 0,          // Watchdog de tâche (software)
   WDT_TYPE_INTERRUPT,         // Watchdog d'interruption
   WDT_TYPE_MAIN_LOOP,         // Watchdog de boucle principale
   WDT_TYPE_COMMUNICATION,     // Watchdog de communication
   WDT_TYPE_HARDWARE,          // Watchdog hardware
   WDT_TYPE_CUSTOM            // Watchdog personnalisé
} watchdog_type_t;

/**
* @brief États du watchdog
*/
typedef enum {
   WDT_STATE_DISABLED = 0,     // Désactivé
   WDT_STATE_ENABLED,          // Activé et surveillant
   WDT_STATE_WARNING,          // Avertissement (proche du timeout)
   WDT_STATE_TIMEOUT,          // Timeout détecté
   WDT_STATE_RECOVERY,         // En cours de récupération
   WDT_STATE_FAILED           // Échec de récupération
} watchdog_state_t;

/**
* @brief Actions de récupération
*/
typedef enum {
   WDT_ACTION_NONE = 0,        // Aucune action
   WDT_ACTION_LOG,             // Log seulement
   WDT_ACTION_RESET_TASK,      // Redémarrer la tâche
   WDT_ACTION_RESET_SYSTEM,    // Redémarrer le système
   WDT_ACTION_SAFE_MODE,       // Mode sécurisé
   WDT_ACTION_CUSTOM          // Action personnalisée
} watchdog_action_t;

/**
* @brief Configuration d'un watchdog
*/
typedef struct {
   watchdog_type_t type;       // Type de watchdog
   uint32_t timeout_ms;        // Timeout en millisecondes
   watchdog_action_t action;   // Action en cas de timeout
   bool auto_reset;            // Reset automatique
   bool enabled;               // Activé/désactivé
   const char* name;           // Nom du watchdog
   void (*callback)(void);     // Callback optionnel
} watchdog_config_t;

/**
* @brief Informations d'un watchdog
*/
typedef struct {
   watchdog_config_t config;   // Configuration
   watchdog_state_t state;     // État actuel
   unsigned long last_feed;    // Dernier feed (ms)
   unsigned long last_timeout; // Dernier timeout (ms)
   uint32_t timeout_count;     // Nombre de timeouts
   uint32_t feed_count;        // Nombre de feeds
   bool is_registered;         // Enregistré dans le système
} watchdog_info_t;

/**
* @brief Statistiques globales du watchdog
*/
typedef struct {
   uint32_t total_watchdogs;   // Nombre total de watchdogs
   uint32_t active_watchdogs;  // Nombre de watchdogs actifs
   uint32_t total_timeouts;    // Nombre total de timeouts
   uint32_t total_resets;      // Nombre total de resets
   unsigned long uptime;       // Temps de fonctionnement
   unsigned long last_reset;   // Dernier reset système
   esp_reset_reason_t reset_reason; // Raison du dernier reset
} watchdog_stats_t;

/**
* @brief Gestionnaire de surveillance (Watchdog)
*/
class WatchdogManager {
public:
   /**
    * @brief Constructeur
    */
   WatchdogManager();

   /**
    * @brief Destructeur
    */
   ~WatchdogManager();

   /**
    * @brief Initialise le gestionnaire de watchdog
    * @return true si succès, false sinon
    */
   bool init();

   /**
    * @brief Boucle principale de surveillance
    */
   void loop();

   /**
    * @brief Arrête tous les watchdogs
    */
   void shutdown();

   // ========================================================================
   // GESTION DES WATCHDOGS
   // ========================================================================

   /**
    * @brief Enregistre un nouveau watchdog
    * @param config Configuration du watchdog
    * @return ID du watchdog (-1 si erreur)
    */
   int registerWatchdog(const watchdog_config_t& config);

   /**
    * @brief Supprime un watchdog
    * @param watchdog_id ID du watchdog
    * @return true si succès, false sinon
    */
   bool unregisterWatchdog(int watchdog_id);

   /**
    * @brief Active/désactive un watchdog
    * @param watchdog_id ID du watchdog
    * @param enable true pour activer, false pour désactiver
    * @return true si succès, false sinon
    */
   bool enableWatchdog(int watchdog_id, bool enable);

   /**
    * @brief Nourrit un watchdog (reset du timer)
    * @param watchdog_id ID du watchdog
    * @return true si succès, false sinon
    */
   bool feedWatchdog(int watchdog_id);

   /**
    * @brief Nourrit tous les watchdogs actifs
    */
   void feedAllWatchdogs();

   // ========================================================================
   // WATCHDOGS PRÉDÉFINIS
   // ========================================================================

   /**
    * @brief Enregistre le watchdog de la boucle principale
    * @param timeout_ms Timeout en millisecondes
    * @return ID du watchdog
    */
   int registerMainLoopWatchdog(uint32_t timeout_ms = 30000);

   /**
    * @brief Enregistre le watchdog de communication
    * @param timeout_ms Timeout en millisecondes
    * @return ID du watchdog
    */
   int registerCommWatchdog(uint32_t timeout_ms = 60000);

   /**
    * @brief Enregistre le watchdog de tâche
    * @param task_name Nom de la tâche
    * @param timeout_ms Timeout en millisecondes
    * @return ID du watchdog
    */
   int registerTaskWatchdog(const char* task_name, uint32_t timeout_ms = 10000);

   /**
    * @brief Nourrit le watchdog de la boucle principale
    */
   void feedMainLoop();

   /**
    * @brief Nourrit le watchdog de communication
    */
   void feedCommunication();

   /**
    * @brief Nourrit le watchdog d'une tâche
    * @param task_name Nom de la tâche
    */
   void feedTask(const char* task_name);

   // ========================================================================
   // CONFIGURATION ET CONTRÔLE
   // ========================================================================

   /**
    * @brief Configure le timeout global
    * @param timeout_ms Timeout en millisecondes
    */
   void setGlobalTimeout(uint32_t timeout_ms);

   /**
    * @brief Active/désactive tous les watchdogs
    * @param enable true pour activer, false pour désactiver
    */
   void enableAll(bool enable);

   /**
    * @brief Configure l'action par défaut en cas de timeout
    * @param action Action à effectuer
    */
   void setDefaultAction(watchdog_action_t action);

   /**
    * @brief Active/désactive le mode debug
    * @param enable true pour activer, false pour désactiver
    */
   void setDebugMode(bool enable);

   /**
    * @brief Configure un callback global de timeout
    * @param callback Fonction de callback
    */
   void setGlobalTimeoutCallback(void (*callback)(int watchdog_id));

   // ========================================================================
   // SURVEILLANCE ET DIAGNOSTIC
   // ========================================================================

   /**
    * @brief Obtient l'état d'un watchdog
    * @param watchdog_id ID du watchdog
    * @return État du watchdog
    */
   watchdog_state_t getWatchdogState(int watchdog_id);

   /**
    * @brief Obtient les informations d'un watchdog
    * @param watchdog_id ID du watchdog
    * @return Informations du watchdog
    */
   watchdog_info_t getWatchdogInfo(int watchdog_id);

   /**
    * @brief Obtient les statistiques globales
    * @return Statistiques du système de watchdog
    */
   watchdog_stats_t getStats();

   /**
    * @brief Vérifie si le système est sain
    * @return true si tous les watchdogs sont OK
    */
   bool isSystemHealthy();

   /**
    * @brief Obtient le nombre de watchdogs actifs
    * @return Nombre de watchdogs actifs
    */
   uint32_t getActiveWatchdogCount();

   /**
    * @brief Obtient la raison du dernier reset
    * @return Raison du reset
    */
   esp_reset_reason_t getLastResetReason();

   // ========================================================================
   // ACTIONS DE RÉCUPÉRATION
   // ========================================================================

   /**
    * @brief Force un reset système
    * @param reason Raison du reset
    */
   void forceSystemReset(const char* reason = "Manual reset");

   /**
    * @brief Entre en mode sécurisé
    */
   void enterSafeMode();

   /**
    * @brief Tente une récupération automatique
    * @param watchdog_id ID du watchdog en timeout
    * @return true si récupération réussie
    */
   bool attemptRecovery(int watchdog_id);

   /**
    * @brief Redémarre une tâche spécifique
    * @param task_name Nom de la tâche
    * @return true si succès
    */
   bool restartTask(const char* task_name);

   // ========================================================================
   // LOGS ET RAPPORTS
   // ========================================================================

   /**
    * @brief Affiche l'état de tous les watchdogs
    */
   void printWatchdogStatus();

   /**
    * @brief Affiche les statistiques détaillées
    */
   void printDetailedStats();

   /**
    * @brief Génère un rapport de santé du système
    */
   void generateHealthReport();

   /**
    * @brief Réinitialise les statistiques
    */
   void resetStats();

   /**
    * @brief Sauvegarde les logs de watchdog
    */
   void saveLogs();

   // ========================================================================
   // TESTS ET VALIDATION
   // ========================================================================

   /**
    * @brief Teste un watchdog spécifique
    * @param watchdog_id ID du watchdog à tester
    * @return true si test réussi
    */
   bool testWatchdog(int watchdog_id);

   /**
    * @brief Simule un timeout pour test
    * @param watchdog_id ID du watchdog
    */
   void simulateTimeout(int watchdog_id);

   /**
    * @brief Lance les tests automatiques
    * @return true si tous les tests passent
    */
   bool runSelfTest();

private:
   // Configuration
   static const int MAX_WATCHDOGS = 16;
   watchdog_info_t watchdogs[MAX_WATCHDOGS];
   int watchdog_count;
   
   // État global
   bool initialized;
   bool debug_mode;
   bool safe_mode;
   uint32_t global_timeout;
   watchdog_action_t default_action;
   
   // Callbacks
   void (*global_timeout_callback)(int watchdog_id);
   
   // Statistiques
   watchdog_stats_t stats;
   unsigned long start_time;
   
   // IDs des watchdogs prédéfinis
   int main_loop_wdt_id;
   int comm_wdt_id;
   
   // Méthodes privées
   int findFreeSlot();
   int findWatchdogById(int watchdog_id);
   int findWatchdogByName(const char* name);
   void checkTimeouts();
   void handleTimeout(int watchdog_id);
   void executeAction(int watchdog_id, watchdog_action_t action);
   void updateStats();
   void logEvent(int watchdog_id, const char* event);
   bool isValidWatchdogId(int watchdog_id);
   void initializeHardwareWatchdog();
   void configureTaskWatchdog();
};

#endif // WATCHDOG_MANAGER_H
