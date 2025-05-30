#ifndef OCPP_WRAPPER_H
#define OCPP_WRAPPER_H

/**
 * @file ocpp_wrapper.h
 * @brief Wrapper autour de MicroOCPP pour simplifier l'utilisation
 * 
 * Issue: [INFRA] Project Structure Setup - MicroOCPP Integration
 * 
 * Cette classe fournit une interface simplifiée et adaptée à nos besoins
 * pour utiliser MicroOCPP dans notre projet ESP32.
 */

#include <Arduino.h>
#include <functional>

/**
 * @brief Wrapper autour de MicroOCPP
 */
class OCPPWrapper {
public:
    /**
     * @brief Types de callbacks
     */
    typedef std::function<void(const char* message)> LogCallback;
    typedef std::function<void(int connectorId, const char* status)> StatusCallback;
    typedef std::function<void(int transactionId, const char* idTag)> TransactionCallback;
    
    /**
     * @brief Constructeur
     */
    OCPPWrapper();
    
    /**
     * @brief Destructeur
     */
    ~OCPPWrapper();
    
    /**
     * @brief Initialise le wrapper OCPP
     * @param wsUrl URL du serveur WebSocket OCPP
     * @param chargePointId ID du point de charge
     * @return true si succès, false sinon
     */
    bool init(const char* wsUrl, const char* chargePointId);
    
    /**
     * @brief Boucle principale à appeler dans loop()
     */
    void loop();
    
    /**
     * @brief Vérifie si connecté au serveur OCPP
     * @return true si connecté, false sinon
     */
    bool isConnected();
    
    /**
     * @brief Définit le statut d'un connecteur
     * @param connectorId ID du connecteur
     * @param status Statut (Available, Preparing, Charging, etc.)
     */
    void setConnectorStatus(int connectorId, const char* status);
    
    /**
     * @brief Démarre une transaction
     * @param connectorId ID du connecteur
     * @param idTag Tag d'identification
     * @return ID de transaction ou -1 si erreur
     */
    int startTransaction(int connectorId, const char* idTag);
    
    /**
     * @brief Arrête une transaction
     * @param connectorId ID du connecteur
     * @return true si succès, false sinon
     */
    bool stopTransaction(int connectorId);
    
    /**
     * @brief Envoie des valeurs de compteur
     * @param connectorId ID du connecteur
     * @param energy Énergie en Wh
     * @param power Puissance en W
     */
    void sendMeterValues(int connectorId, float energy, float power);
    
    /**
     * @brief Configure le callback de log
     * @param callback Fonction de callback
     */
    void setLogCallback(LogCallback callback);
    
    /**
     * @brief Configure le callback de changement de statut
     * @param callback Fonction de callback
     */
    void setStatusCallback(StatusCallback callback);
    
    /**
     * @brief Configure le callback de transaction
     * @param callback Fonction de callback
     */
    void setTransactionCallback(TransactionCallback callback);
    
    /**
     * @brief Obtient la configuration OCPP
     * @param key Clé de configuration
     * @return Valeur ou nullptr si non trouvée
     */
    const char* getConfiguration(const char* key);
    
    /**
     * @brief Définit une configuration OCPP
     * @param key Clé de configuration
     * @param value Valeur
     * @return true si succès, false sinon
     */
    bool setConfiguration(const char* key, const char* value);

private:
    // Variables privées
    char* wsUrl;
    char* chargePointId;
    bool initialized;
    bool connected;
    
    // Callbacks
    LogCallback logCallback;
    StatusCallback statusCallback;
    TransactionCallback transactionCallback;
    
    // Méthodes privées
    void logMessage(const char* message);
    void handleStatusChange(int connectorId, const char* status);
    void handleTransaction(int transactionId, const char* idTag);
};

#endif // OCPP_WRAPPER_H
