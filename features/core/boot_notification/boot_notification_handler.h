#ifndef BOOT_NOTIFICATION_HANDLER_H
#define BOOT_NOTIFICATION_HANDLER_H

#include <ArduinoJson.h>
#include <string>

/**
 * @brief Gestionnaire pour la fonctionnalité BootNotification OCPP 1.6
 * 
 * Issue GitHub: #001 - [CORE] Implémentation BootNotification
 * 
 * Cette classe gère l'envoi de notifications de démarrage au serveur OCPP
 * conformément à la spécification OCPP 1.6 section 4.1
 */
class BootNotificationHandler {
public:
    /**
     * @brief Structure pour les données de BootNotification
     */
    struct BootNotificationData {
        String chargePointVendor;
        String chargePointModel;
        String chargePointSerialNumber;
        String chargeBoxSerialNumber;
        String firmwareVersion;
        String iccid;
        String imsi;
        String meterType;
        String meterSerialNumber;
    };

    /**
     * @brief Énumération des statuts de réponse
     */
    enum class BootNotificationStatus {
        ACCEPTED,
        PENDING,
        REJECTED
    };

    /**
     * @brief Structure pour la réponse BootNotification
     */
    struct BootNotificationResponse {
        BootNotificationStatus status;
        String currentTime;
        int interval;
    };

    /**
     * @brief Constructeur
     */
    BootNotificationHandler();

    /**
     * @brief Crée une requête BootNotification
     * @param data Données du point de charge
     * @return JSON de la requête
     */
    DynamicJsonDocument createRequest(const BootNotificationData& data);

    /**
     * @brief Parse une réponse BootNotification
     * @param response JSON de la réponse
     * @return Structure de réponse parsée
     */
    BootNotificationResponse parseResponse(const DynamicJsonDocument& response);

    /**
     * @brief Valide une requête BootNotification
     * @param request JSON à valider
     * @return true si valide, false sinon
     */
    bool validateRequest(const DynamicJsonDocument& request);

    /**
     * @brief Valide une réponse BootNotification
     * @param response JSON à valider
     * @return true si valide, false sinon
     */
    bool validateResponse(const DynamicJsonDocument& response);

private:
    /**
     * @brief Valide les champs obligatoires
     */
    bool validateRequiredFields(const DynamicJsonDocument& doc);
    
    /**
     * @brief Valide les longueurs de chaînes
     */
    bool validateStringLengths(const DynamicJsonDocument& doc);
};

#endif // BOOT_NOTIFICATION_HANDLER_H
