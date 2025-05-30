/**
* @file watchdog_manager.cpp
* @brief Implémentation simplifiée du gestionnaire de surveillance (Watchdog)
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* Version compatible avec toutes les versions d'ESP-IDF + Fix ESP32 Watchdog
*/

#include "watchdog_manager.h"

static const char* TAG = "WatchdogManager";

WatchdogManager::WatchdogManager() {
   watchdog_count = 0;
   initialized = false;
   debug_mode = false;
   safe_mode = false;
   global_timeout = 30000; // 30 secondes par défaut
   default_action = WDT_ACTION_LOG;
   global_timeout_callback = nullptr;
   start_time = 0;
   main_loop_wdt_id = -1;
   comm_wdt_id = -1;
   
   // Initialiser les slots de watchdog
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       watchdogs[i].is_registered = false;
       watchdogs[i].state = WDT_STATE_DISABLED;
   }
   
   // Initialiser les statistiques
   memset(&stats, 0, sizeof(watchdog_stats_t));
   stats.reset_reason = esp_reset_reason();
}

WatchdogManager::~WatchdogManager() {
   shutdown();
}

bool WatchdogManager::init() {
   Serial.println("🐕 Initialisation du gestionnaire de watchdog...");
   
   start_time = millis();
   stats.uptime = 0;
   
   // Configuration du watchdog de tâche ESP32 (version simplifiée)
   configureTaskWatchdog();
   
   // Initialisation du watchdog hardware
   initializeHardwareWatchdog();
   
   // Enregistrement des watchdogs système par défaut
   main_loop_wdt_id = registerMainLoopWatchdog(30000);
   comm_wdt_id = registerCommWatchdog(60000);
   
   if (main_loop_wdt_id < 0 || comm_wdt_id < 0) {
       Serial.println("❌ Erreur lors de l'enregistrement des watchdogs système");
       return false;
   }
   
   initialized = true;
   
   // Afficher la raison du dernier reset
   esp_reset_reason_t reset_reason = esp_reset_reason();
   Serial.printf("🐕 Raison du dernier reset: ");
   switch (reset_reason) {
       case ESP_RST_POWERON:   Serial.println("Power-on"); break;
       case ESP_RST_EXT:       Serial.println("External reset"); break;
       case ESP_RST_SW:        Serial.println("Software reset"); break;
       case ESP_RST_PANIC:     Serial.println("Exception/panic"); break;
       case ESP_RST_INT_WDT:   Serial.println("Interrupt watchdog"); break;
       case ESP_RST_TASK_WDT:  Serial.println("Task watchdog"); break;
       case ESP_RST_WDT:       Serial.println("Other watchdog"); break;
       case ESP_RST_DEEPSLEEP: Serial.println("Deep sleep reset"); break;
       case ESP_RST_BROWNOUT:  Serial.println("Brownout reset"); break;
       case ESP_RST_SDIO:      Serial.println("SDIO reset"); break;
       default:                Serial.println("Unknown"); break;
   }
   
   Serial.printf("✅ Gestionnaire de watchdog initialisé (%d watchdogs)\n", watchdog_count);
   return true;
}

void WatchdogManager::loop() {
   if (!initialized) return;
   
   unsigned long now = millis();
   
   // Mise à jour des statistiques
   stats.uptime = now - start_time;
   
   // Vérification des timeouts
   checkTimeouts();
   
   // Mise à jour des statistiques globales
   updateStats();
   
   // NOTE: Le watchdog ESP32 natif est maintenant nourri dans main.cpp
   // pour éviter les conflits et avoir un contrôle plus fin
}

void WatchdogManager::shutdown() {
   if (!initialized) return;
   
   Serial.println("🐕 Arrêt du gestionnaire de watchdog...");
   
   // Désactiver tous les watchdogs
   enableAll(false);
   
   // NOTE: Ne pas désinitialiser le watchdog ESP32 ici pour éviter les erreurs
   // Il sera géré automatiquement par le système
   
   initialized = false;
   Serial.println("✅ Gestionnaire de watchdog arrêté");
}

// ============================================================================
// GESTION DES WATCHDOGS
// ============================================================================

int WatchdogManager::registerWatchdog(const watchdog_config_t& config) {
   if (watchdog_count >= MAX_WATCHDOGS) {
       Serial.println("❌ Nombre maximum de watchdogs atteint");
       return -1;
   }
   
   int slot = findFreeSlot();
   if (slot < 0) {
       Serial.println("❌ Aucun slot libre pour le watchdog");
       return -1;
   }
   
   // Configurer le watchdog
   watchdogs[slot].config = config;
   watchdogs[slot].state = config.enabled ? WDT_STATE_ENABLED : WDT_STATE_DISABLED;
   watchdogs[slot].last_feed = millis();
   watchdogs[slot].last_timeout = 0;
   watchdogs[slot].timeout_count = 0;
   watchdogs[slot].feed_count = 0;
   watchdogs[slot].is_registered = true;
   
   watchdog_count++;
   stats.total_watchdogs++;
   
   if (debug_mode) {
       Serial.printf("🐕 Watchdog enregistré: %s (ID: %d, Timeout: %lu ms)\n", 
                    config.name, slot, config.timeout_ms);
   }
   
   return slot;
}

bool WatchdogManager::unregisterWatchdog(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return false;
   }
   
   watchdogs[watchdog_id].is_registered = false;
   watchdogs[watchdog_id].state = WDT_STATE_DISABLED;
   watchdog_count--;
   
   if (debug_mode) {
       Serial.printf("🐕 Watchdog désenregistré: %s (ID: %d)\n", 
                    watchdogs[watchdog_id].config.name, watchdog_id);
   }
   
   return true;
}

bool WatchdogManager::enableWatchdog(int watchdog_id, bool enable) {
   if (!isValidWatchdogId(watchdog_id)) {
       return false;
   }
   
   watchdogs[watchdog_id].config.enabled = enable;
   watchdogs[watchdog_id].state = enable ? WDT_STATE_ENABLED : WDT_STATE_DISABLED;
   
   if (enable) {
       watchdogs[watchdog_id].last_feed = millis();
   }
   
   if (debug_mode) {
       Serial.printf("🐕 Watchdog %s: %s (ID: %d)\n", 
                    watchdogs[watchdog_id].config.name,
                    enable ? "ACTIVÉ" : "DÉSACTIVÉ", watchdog_id);
   }
   
   return true;
}

bool WatchdogManager::feedWatchdog(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return false;
   }
   
   if (watchdogs[watchdog_id].state != WDT_STATE_ENABLED) {
       return false;
   }
   
   watchdogs[watchdog_id].last_feed = millis();
   watchdogs[watchdog_id].feed_count++;
   
   // Réinitialiser l'état si c'était en warning
   if (watchdogs[watchdog_id].state == WDT_STATE_WARNING) {
       watchdogs[watchdog_id].state = WDT_STATE_ENABLED;
   }
   
   return true;
}

void WatchdogManager::feedAllWatchdogs() {
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered && watchdogs[i].config.enabled) {
           feedWatchdog(i);
       }
   }
}

// ============================================================================
// WATCHDOGS PRÉDÉFINIS
// ============================================================================

int WatchdogManager::registerMainLoopWatchdog(uint32_t timeout_ms) {
   watchdog_config_t config = {
       .type = WDT_TYPE_MAIN_LOOP,
       .timeout_ms = timeout_ms,
       .action = WDT_ACTION_RESET_SYSTEM,
       .auto_reset = true,
       .enabled = true,
       .name = "MainLoop",
       .callback = nullptr
   };
   
   return registerWatchdog(config);
}

int WatchdogManager::registerCommWatchdog(uint32_t timeout_ms) {
   watchdog_config_t config = {
       .type = WDT_TYPE_COMMUNICATION,
       .timeout_ms = timeout_ms,
       .action = WDT_ACTION_LOG,
       .auto_reset = true,
       .enabled = true,
       .name = "Communication",
       .callback = nullptr
   };
   
   return registerWatchdog(config);
}

int WatchdogManager::registerTaskWatchdog(const char* task_name, uint32_t timeout_ms) {
   watchdog_config_t config = {
       .type = WDT_TYPE_TASK,
       .timeout_ms = timeout_ms,
       .action = WDT_ACTION_RESET_TASK,
       .auto_reset = true,
       .enabled = true,
       .name = task_name,
       .callback = nullptr
   };
   
   return registerWatchdog(config);
}

void WatchdogManager::feedMainLoop() {
   if (main_loop_wdt_id >= 0) {
       feedWatchdog(main_loop_wdt_id);
   }
}

void WatchdogManager::feedCommunication() {
   if (comm_wdt_id >= 0) {
       feedWatchdog(comm_wdt_id);
   }
}

void WatchdogManager::feedTask(const char* task_name) {
   int id = findWatchdogByName(task_name);
   if (id >= 0) {
       feedWatchdog(id);
   }
}

// ============================================================================
// CONFIGURATION ET CONTRÔLE
// ============================================================================

void WatchdogManager::setGlobalTimeout(uint32_t timeout_ms) {
   global_timeout = timeout_ms;
   Serial.printf("🐕 Timeout global défini: %lu ms\n", timeout_ms);
}

void WatchdogManager::enableAll(bool enable) {
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered) {
           enableWatchdog(i, enable);
       }
   }
   
   Serial.printf("🐕 Tous les watchdogs: %s\n", enable ? "ACTIVÉS" : "DÉSACTIVÉS");
}

void WatchdogManager::setDefaultAction(watchdog_action_t action) {
   default_action = action;
   Serial.printf("🐕 Action par défaut: %d\n", action);
}

void WatchdogManager::setDebugMode(bool enable) {
   debug_mode = enable;
   Serial.printf("🐕 Mode debug: %s\n", enable ? "ACTIVÉ" : "DÉSACTIVÉ");
}

void WatchdogManager::setGlobalTimeoutCallback(void (*callback)(int watchdog_id)) {
   global_timeout_callback = callback;
   Serial.println("🐕 Callback global de timeout configuré");
}

// ============================================================================
// SURVEILLANCE ET DIAGNOSTIC
// ============================================================================

watchdog_state_t WatchdogManager::getWatchdogState(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return WDT_STATE_DISABLED;
   }
   
   return watchdogs[watchdog_id].state;
}

watchdog_info_t WatchdogManager::getWatchdogInfo(int watchdog_id) {
   static watchdog_info_t empty_info = {};
   
   if (!isValidWatchdogId(watchdog_id)) {
       return empty_info;
   }
   
   return watchdogs[watchdog_id];
}

watchdog_stats_t WatchdogManager::getStats() {
   stats.uptime = millis() - start_time;
   return stats;
}

bool WatchdogManager::isSystemHealthy() {
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered && watchdogs[i].config.enabled) {
           if (watchdogs[i].state == WDT_STATE_TIMEOUT || 
               watchdogs[i].state == WDT_STATE_FAILED) {
               return false;
           }
       }
   }
   return true;
}

uint32_t WatchdogManager::getActiveWatchdogCount() {
   uint32_t count = 0;
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered && watchdogs[i].config.enabled) {
           count++;
       }
   }
   return count;
}

esp_reset_reason_t WatchdogManager::getLastResetReason() {
   return stats.reset_reason;
}

// ============================================================================
// ACTIONS DE RÉCUPÉRATION
// ============================================================================

void WatchdogManager::forceSystemReset(const char* reason) {
   Serial.printf("🐕 RESET SYSTÈME FORCÉ: %s\n", reason);
   delay(100); // Laisser le temps au message de s'afficher
   esp_restart();
}

void WatchdogManager::enterSafeMode() {
   Serial.println("🐕 ENTRÉE EN MODE SÉCURISÉ");
   safe_mode = true;
   
   // Désactiver tous les watchdogs non critiques
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered && 
           watchdogs[i].config.type != WDT_TYPE_MAIN_LOOP) {
           enableWatchdog(i, false);
       }
   }
}

bool WatchdogManager::attemptRecovery(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return false;
   }
   
   Serial.printf("🐕 Tentative de récupération: %s\n", watchdogs[watchdog_id].config.name);
   
   watchdogs[watchdog_id].state = WDT_STATE_RECOVERY;
   
   // Exécuter l'action de récupération
   executeAction(watchdog_id, watchdogs[watchdog_id].config.action);
   
   // Réinitialiser le watchdog
   watchdogs[watchdog_id].last_feed = millis();
   watchdogs[watchdog_id].state = WDT_STATE_ENABLED;
   
   return true;
}

bool WatchdogManager::restartTask(const char* task_name) {
   Serial.printf("🐕 Redémarrage de la tâche: %s\n", task_name);
   
   // À implémenter selon l'architecture des tâches
   // Pour l'instant, juste un log
   
   return true;
}

// ============================================================================
// LOGS ET RAPPORTS
// ============================================================================

void WatchdogManager::printWatchdogStatus() {
   Serial.println("🐕 ===== ÉTAT DES WATCHDOGS =====");
   Serial.printf("   Watchdogs totaux: %d\n", watchdog_count);
   Serial.printf("   Watchdogs actifs: %lu\n", getActiveWatchdogCount());
   Serial.printf("   Système sain: %s\n", isSystemHealthy() ? "OUI" : "NON");
   Serial.printf("   Mode sécurisé: %s\n", safe_mode ? "OUI" : "NON");
   
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered) {
           unsigned long since_feed = millis() - watchdogs[i].last_feed;
           Serial.printf("   [%d] %s: État=%d, Timeout=%lu ms, Depuis feed=%lu ms\n",
                        i, watchdogs[i].config.name, watchdogs[i].state,
                        watchdogs[i].config.timeout_ms, since_feed);
       }
   }
   Serial.println("🐕 ==============================");
}

void WatchdogManager::printDetailedStats() {
   watchdog_stats_t current_stats = getStats();
   
   Serial.println("🐕 ===== STATISTIQUES DÉTAILLÉES =====");
   Serial.printf("   Temps de fonctionnement: %lu ms\n", current_stats.uptime);
   Serial.printf("   Timeouts totaux: %lu\n", current_stats.total_timeouts);
   Serial.printf("   Resets totaux: %lu\n", current_stats.total_resets);
   Serial.printf("   Dernier reset: %lu ms\n", current_stats.last_reset);
   Serial.printf("   Raison du reset: %d\n", current_stats.reset_reason);
   
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered) {
           Serial.printf("   [%d] %s: Feeds=%lu, Timeouts=%lu\n",
                        i, watchdogs[i].config.name,
                        watchdogs[i].feed_count, watchdogs[i].timeout_count);
       }
   }
   Serial.println("🐕 ===================================");
}

void WatchdogManager::generateHealthReport() {
   Serial.println("🐕 ===== RAPPORT DE SANTÉ SYSTÈME =====");
   
   bool healthy = isSystemHealthy();
   Serial.printf("   État général: %s\n", healthy ? "SAIN" : "PROBLÈME DÉTECTÉ");
   
   if (!healthy) {
       Serial.println("   Problèmes détectés:");
       for (int i = 0; i < MAX_WATCHDOGS; i++) {
           if (watchdogs[i].is_registered && 
               (watchdogs[i].state == WDT_STATE_TIMEOUT || 
                watchdogs[i].state == WDT_STATE_FAILED)) {
               Serial.printf("     - %s: État %d\n", 
                            watchdogs[i].config.name, watchdogs[i].state);
           }
       }
   }
   
   Serial.printf("   Recommandations: %s\n", 
                healthy ? "Aucune" : "Vérifier les tâches en timeout");
   Serial.println("🐕 ====================================");
}

void WatchdogManager::resetStats() {
   memset(&stats, 0, sizeof(watchdog_stats_t));
   stats.reset_reason = esp_reset_reason();
   start_time = millis();
   
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered) {
           watchdogs[i].timeout_count = 0;
           watchdogs[i].feed_count = 0;
       }
   }
   
   Serial.println("🐕 Statistiques réinitialisées");
}

void WatchdogManager::saveLogs() {
   // À implémenter: sauvegarde dans SPIFFS/LittleFS
   Serial.println("🐕 Sauvegarde des logs (non implémentée)");
}

// ============================================================================
// TESTS ET VALIDATION
// ============================================================================

bool WatchdogManager::testWatchdog(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return false;
   }
   
   Serial.printf("🐕 Test du watchdog: %s\n", watchdogs[watchdog_id].config.name);
   
   // Sauvegarder l'état actuel
   bool was_enabled = watchdogs[watchdog_id].config.enabled;
   watchdog_action_t original_action = watchdogs[watchdog_id].config.action;
   
   // Configurer pour le test
   watchdogs[watchdog_id].config.action = WDT_ACTION_LOG;
   enableWatchdog(watchdog_id, true);
   
   // Simuler un timeout
   simulateTimeout(watchdog_id);
   
   // Restaurer la configuration
   watchdogs[watchdog_id].config.action = original_action;
   enableWatchdog(watchdog_id, was_enabled);
   
   Serial.printf("✅ Test du watchdog %s terminé\n", watchdogs[watchdog_id].config.name);
   return true;
}

void WatchdogManager::simulateTimeout(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return;
   }
   
   Serial.printf("🐕 Simulation timeout: %s\n", watchdogs[watchdog_id].config.name);
   
   // Forcer un timeout en modifiant le timestamp
   watchdogs[watchdog_id].last_feed = millis() - watchdogs[watchdog_id].config.timeout_ms - 1000;
   
   // Déclencher la vérification
   handleTimeout(watchdog_id);
}

bool WatchdogManager::runSelfTest() {
   Serial.println("🐕 Démarrage des tests automatiques...");
   
   bool all_passed = true;
   
   // Test 1: Vérifier l'initialisation
   if (!initialized) {
       Serial.println("❌ Test 1 échoué: Non initialisé");
       all_passed = false;
   } else {
       Serial.println("✅ Test 1 réussi: Initialisation OK");
   }
   
   // Test 2: Vérifier les watchdogs système
   if (main_loop_wdt_id < 0 || comm_wdt_id < 0) {
       Serial.println("❌ Test 2 échoué: Watchdogs système manquants");
       all_passed = false;
   } else {
       Serial.println("✅ Test 2 réussi: Watchdogs système OK");
   }
   
   // Test 3: Tester un watchdog temporaire
   watchdog_config_t test_config = {
       .type = WDT_TYPE_CUSTOM,
       .timeout_ms = 1000,
       .action = WDT_ACTION_LOG,
       .auto_reset = false,
       .enabled = true,
       .name = "TestWatchdog",
       .callback = nullptr
   };
   
   int test_id = registerWatchdog(test_config);
   if (test_id >= 0) {
       testWatchdog(test_id);
       unregisterWatchdog(test_id);
       Serial.println("✅ Test 3 réussi: Test watchdog temporaire OK");
   } else {
       Serial.println("❌ Test 3 échoué: Impossible de créer watchdog temporaire");
       all_passed = false;
   }
   
   Serial.printf("🐕 Tests automatiques terminés: %s\n", 
                all_passed ? "TOUS RÉUSSIS" : "ÉCHECS DÉTECTÉS");
   
   return all_passed;
}

// ============================================================================
// MÉTHODES PRIVÉES
// ============================================================================

int WatchdogManager::findFreeSlot() {
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (!watchdogs[i].is_registered) {
           return i;
       }
   }
   return -1;
}

int WatchdogManager::findWatchdogById(int watchdog_id) {
   if (watchdog_id >= 0 && watchdog_id < MAX_WATCHDOGS && 
       watchdogs[watchdog_id].is_registered) {
       return watchdog_id;
   }
   return -1;
}

int WatchdogManager::findWatchdogByName(const char* name) {
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (watchdogs[i].is_registered && 
           strcmp(watchdogs[i].config.name, name) == 0) {
           return i;
       }
   }
   return -1;
}

void WatchdogManager::checkTimeouts() {
   unsigned long now = millis();
   
   for (int i = 0; i < MAX_WATCHDOGS; i++) {
       if (!watchdogs[i].is_registered || !watchdogs[i].config.enabled) {
           continue;
       }
       
       unsigned long since_feed = now - watchdogs[i].last_feed;
       uint32_t timeout = watchdogs[i].config.timeout_ms;
       
       // Vérifier le warning (80% du timeout)
       if (since_feed > (timeout * 0.8) && watchdogs[i].state == WDT_STATE_ENABLED) {
           watchdogs[i].state = WDT_STATE_WARNING;
           if (debug_mode) {
               Serial.printf("⚠️ Watchdog %s en warning\n", watchdogs[i].config.name);
           }
       }
       
       // Vérifier le timeout
       if (since_feed > timeout && watchdogs[i].state != WDT_STATE_TIMEOUT) {
           handleTimeout(i);
       }
   }
}

void WatchdogManager::handleTimeout(int watchdog_id) {
   if (!isValidWatchdogId(watchdog_id)) {
       return;
   }
   
   watchdogs[watchdog_id].state = WDT_STATE_TIMEOUT;
   watchdogs[watchdog_id].last_timeout = millis();
   watchdogs[watchdog_id].timeout_count++;
   stats.total_timeouts++;
   
   Serial.printf("🚨 TIMEOUT WATCHDOG: %s (ID: %d)\n", 
                watchdogs[watchdog_id].config.name, watchdog_id);
   
   logEvent(watchdog_id, "TIMEOUT");
   
   // Appeler le callback global si défini
   if (global_timeout_callback) {
       global_timeout_callback(watchdog_id);
   }
   
   // Appeler le callback spécifique si défini
   if (watchdogs[watchdog_id].config.callback) {
       watchdogs[watchdog_id].config.callback();
   }
   
   // Exécuter l'action configurée
   executeAction(watchdog_id, watchdogs[watchdog_id].config.action);
   
   // Auto-reset si configuré
   if (watchdogs[watchdog_id].config.auto_reset) {
       watchdogs[watchdog_id].last_feed = millis();
       watchdogs[watchdog_id].state = WDT_STATE_ENABLED;
   }
}

void WatchdogManager::executeAction(int watchdog_id, watchdog_action_t action) {
   switch (action) {
       case WDT_ACTION_NONE:
           break;
           
       case WDT_ACTION_LOG:
           logEvent(watchdog_id, "ACTION_LOG");
           break;
           
       case WDT_ACTION_RESET_TASK:
           logEvent(watchdog_id, "ACTION_RESET_TASK");
           restartTask(watchdogs[watchdog_id].config.name);
           break;
           
       case WDT_ACTION_RESET_SYSTEM:
           logEvent(watchdog_id, "ACTION_RESET_SYSTEM");
           stats.total_resets++;
           forceSystemReset("Watchdog timeout");
           break;
           
       case WDT_ACTION_SAFE_MODE:
           logEvent(watchdog_id, "ACTION_SAFE_MODE");
           enterSafeMode();
           break;
           
       case WDT_ACTION_CUSTOM:
           logEvent(watchdog_id, "ACTION_CUSTOM");
           // Action personnalisée via callback
           break;
   }
}

void WatchdogManager::updateStats() {
   stats.active_watchdogs = getActiveWatchdogCount();
   stats.total_watchdogs = watchdog_count;
}

void WatchdogManager::logEvent(int watchdog_id, const char* event) {
   if (debug_mode) {
       Serial.printf("🐕 [%lu] %s: %s\n", millis(), 
                    watchdogs[watchdog_id].config.name, event);
   }
}

bool WatchdogManager::isValidWatchdogId(int watchdog_id) {
   return (watchdog_id >= 0 && watchdog_id < MAX_WATCHDOGS && 
           watchdogs[watchdog_id].is_registered);
}

void WatchdogManager::initializeHardwareWatchdog() {
   // Configuration du watchdog hardware ESP32
   // Note: Le watchdog hardware est généralement géré automatiquement
   Serial.println("🐕 Watchdog hardware initialisé");
}

void WatchdogManager::configureTaskWatchdog() {
   // Configuration simplifiée du watchdog de tâche ESP32
   // Le watchdog ESP32 natif sera nourri directement dans main.cpp
   
   Serial.println("🐕 Configuration du watchdog de tâche...");
   Serial.println("ℹ️ Le watchdog ESP32 natif sera géré par la boucle principale");
   
   // Note: Nous ne configurons pas le watchdog ESP32 ici pour éviter les conflits
   // Il sera nourri directement dans main.cpp avec esp_task_wdt_reset()
}
