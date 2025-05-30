#include "boot_notification_handler.h"
#include <Arduino.h>

BootNotificationHandler::BootNotificationHandler() {
    // Constructeur - initialisation si nécessaire
}

DynamicJsonDocument BootNotificationHandler::createRequest(const BootNotificationData& data) {
    DynamicJsonDocument request(1024);
    
    // Champs obligatoires
    request["chargePointVendor"] = data.chargePointVendor;
    request["chargePointModel"] = data.chargePointModel;
    
    // Champs optionnels
    if (!data.chargePointSerialNumber.isEmpty()) {
        request["chargePointSerialNumber"] = data.chargePointSerialNumber;
    }
    if (!data.chargeBoxSerialNumber.isEmpty()) {
        request["chargeBoxSerialNumber"] = data.chargeBoxSerialNumber;
    }
    if (!data.firmwareVersion.isEmpty()) {
        request["firmwareVersion"] = data.firmwareVersion;
    }
    if (!data.iccid.isEmpty()) {
        request["iccid"] = data.iccid;
    }
    if (!data.imsi.isEmpty()) {
        request["imsi"] = data.imsi;
    }
    if (!data.meterType.isEmpty()) {
        request["meterType"] = data.meterType;
    }
    if (!data.meterSerialNumber.isEmpty()) {
        request["meterSerialNumber"] = data.meterSerialNumber;
    }
    
    return request;
}

BootNotificationHandler::BootNotificationResponse 
BootNotificationHandler::parseResponse(const DynamicJsonDocument& response) {
    BootNotificationResponse result;
    
    // Parse du statut
    String statusStr = response["status"];
    if (statusStr == "Accepted") {
        result.status = BootNotificationStatus::ACCEPTED;
    } else if (statusStr == "Pending") {
        result.status = BootNotificationStatus::PENDING;
    } else {
        result.status = BootNotificationStatus::REJECTED;
    }
    
    result.currentTime = response["currentTime"].as<String>();
    result.interval = response["interval"];
    
    return result;
}

bool BootNotificationHandler::validateRequest(const DynamicJsonDocument& request) {
    // Vérification des champs obligatoires
    if (!request.containsKey("chargePointVendor") || 
        !request.containsKey("chargePointModel")) {
        return false;
    }
    
    // Vérification des longueurs
    if (request["chargePointVendor"].as<String>().length() > 20 ||
        request["chargePointModel"].as<String>().length() > 20) {
        return false;
    }
    
    return validateStringLengths(request);
}

bool BootNotificationHandler::validateResponse(const DynamicJsonDocument& response) {
    // Vérification des champs obligatoires
    if (!response.containsKey("status") || 
        !response.containsKey("currentTime") ||
        !response.containsKey("interval")) {
        return false;
    }
    
    // Vérification du statut
    String status = response["status"];
    if (status != "Accepted" && status != "Pending" && status != "Rejected") {
        return false;
    }
    
    return true;
}

bool BootNotificationHandler::validateStringLengths(const DynamicJsonDocument& doc) {
    // Vérification des longueurs selon OCPP 1.6
    const char* fields[] = {
        "chargePointSerialNumber", "chargeBoxSerialNumber", 
        "iccid", "imsi", "meterType", "meterSerialNumber"
    };
    const int maxLengths[] = {25, 25, 20, 20, 25, 25};
    
    for (int i = 0; i < 6; i++) {
        if (doc.containsKey(fields[i])) {
            if (doc[fields[i]].as<String>().length() > maxLengths[i]) {
                return false;
            }
        }
    }
    
    return true;
}
