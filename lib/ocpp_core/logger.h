#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <stdarg.h>
#include "ocpp_config.h"

/**
 * @brief Système de logging pour OCPP
 * 
 * Issue GitHub: #3 - [INFRA] Logging System
 * 
 * Ce système de logging fournit des fonctionnalités de traçage
 * avec différents niveaux de sévérité et formatage automatique.
 */
class Logger {
public:
    /**
     * @brief Initialise le système de logging
     */
    static void init();

    /**
     * @brief Log un message d'erreur
     * @param tag Tag identifiant le module
     * @param format Format du message (style printf)
     * @param ... Arguments du format
     */
    static void error(const char* tag, const char* format, ...);

    /**
     * @brief Log un message d'avertissement
     * @param tag Tag identifiant le module
     * @param format Format du message (style printf)
     * @param ... Arguments du format
     */
    static void warning(const char* tag, const char* format, ...);

    /**
     * @brief Log un message d'information
     * @param tag Tag identifiant le module
     * @param format Format du message (style printf)
     * @param ... Arguments du format
     */
    static void info(const char* tag, const char* format, ...);

    /**
     * @brief Log un message de debug
     * @param tag Tag identifiant le module
     * @param format Format du message (style printf)
     * @param ... Arguments du format
     */
    static void debug(const char* tag, const char* format, ...);

    /**
     * @brief Définit le niveau de log minimum
     * @param level Niveau minimum à logger
     */
    static void setLevel(log_level_t level);

    /**
     * @brief Obtient le niveau de log actuel
     * @return Niveau de log actuel
     */
    static log_level_t getLevel();

private:
    static void log(log_level_t level, const char* tag, const char* format, va_list args);
    static const char* getLevelString(log_level_t level);
    static bool shouldLog(log_level_t level);
    static log_level_t currentLevel;
};

// Macros pour faciliter l'utilisation
#define LOG_ERROR(tag, ...) Logger::error(tag, __VA_ARGS__)
#define LOG_WARNING(tag, ...) Logger::warning(tag, __VA_ARGS__)
#define LOG_INFO(tag, ...) Logger::info(tag, __VA_ARGS__)
#define LOG_DEBUG(tag, ...) Logger::debug(tag, __VA_ARGS__)

#endif // LOGGER_H
