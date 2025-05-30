# Roadmap des issues OCPP 1.6

## Phase 1 : Fonctionnalités Core (Projet #16)
### Priorité Haute
- [ ] #001 - [CORE] BootNotification
- [ ] #002 - [CORE] Heartbeat  
- [ ] #003 - [CORE] StatusNotification
- [ ] #004 - [CORE] Authorize
- [ ] #005 - [CORE] StartTransaction
- [ ] #006 - [CORE] StopTransaction
- [ ] #007 - [CORE] MeterValues

### Priorité Moyenne
- [ ] #008 - [CORE] DataTransfer

## Phase 2 : Fonctionnalités Optionnelles (Projet #22)
### Firmware Management
- [ ] #101 - [FIRMWARE] UpdateFirmware
- [ ] #102 - [FIRMWARE] FirmwareStatusNotification
- [ ] #103 - [FIRMWARE] GetDiagnostics
- [ ] #104 - [FIRMWARE] DiagnosticsStatusNotification

### Remote Control
- [ ] #201 - [REMOTE] RemoteStartTransaction
- [ ] #202 - [REMOTE] RemoteStopTransaction
- [ ] #203 - [REMOTE] UnlockConnector
- [ ] #204 - [REMOTE] Reset
- [ ] #205 - [REMOTE] ChangeAvailability
- [ ] #206 - [REMOTE] ChangeConfiguration
- [ ] #207 - [REMOTE] GetConfiguration
- [ ] #208 - [REMOTE] ClearCache

### Local Authorization
- [ ] #301 - [LOCAL-AUTH] GetLocalListVersion
- [ ] #302 - [LOCAL-AUTH] SendLocalList

### Reservation
- [ ] #401 - [RESERVATION] ReserveNow
- [ ] #402 - [RESERVATION] CancelReservation

### Smart Charging
- [ ] #501 - [SMART-CHARGING] SetChargingProfile
- [ ] #502 - [SMART-CHARGING] ClearChargingProfile
- [ ] #503 - [SMART-CHARGING] GetCompositeSchedule

### Triggers
- [ ] #601 - [TRIGGER] TriggerMessage

## Estimation des efforts
- **Phase 1** : ~40 heures (2-3 semaines)
- **Phase 2** : ~80 heures (4-6 semaines)
- **Total** : ~120 heures (6-9 semaines)
