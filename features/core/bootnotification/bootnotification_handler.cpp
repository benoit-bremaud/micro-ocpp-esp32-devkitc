#include "bootnotification_handler.h"
#include <MicroOcpp.h>

// Set BootNotification parameters before connecting to the CSMS
void setupBootNotification() {
    setChargePointVendor("VEV");
    setChargePointModel("VEV-Gateway-ESP32");
    setChargeBoxSerialNumber("GW001");
    setFirmwareVersion("v1.0.0");
    // Add other parameters as needed (ICCID, IMSI, etc.)
    // No manual trigger: MicroOcpp sends BootNotification automatically on connection
}
