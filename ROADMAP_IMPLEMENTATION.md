# Roadmap d'Implémentation

## 🎯 Phase 1 : Infrastructure (2-3 semaines)
**Projet** : OCPP Infrastructure

### Sprint 1 : Base technique
- [ ] Configuration ESP32 et PlatformIO
- [ ] Structure des dossiers `features/`
- [ ] Système de logging
- [ ] Configuration WiFi

### Sprint 2 : Communication
- [ ] WebSocket client OCPP
- [ ] JSON parser/validator
- [ ] Message queue system
- [ ] Error handling

### Sprint 3 : Tests et CI
- [ ] Framework de tests Unity
- [ ] Tests d'intégration WebSocket
- [ ] CI/CD GitHub Actions
- [ ] Documentation technique

## 🎯 Phase 2 : Core Features (3-4 semaines)
**Projet** : OCPP Core Features

### Sprint 4 : Authentification et Boot
- [ ] BootNotification
- [ ] Heartbeat
- [ ] Authorize

### Sprint 5 : Transactions
- [ ] StartTransaction
- [ ] StopTransaction
- [ ] MeterValues

### Sprint 6 : Monitoring
- [ ] StatusNotification
- [ ] DataTransfer
- [ ] Tests end-to-end

## 🎯 Phase 3 : Features Avancées (4-6 semaines)
**Projets** : Remote Control, Firmware, etc.

### Sprint 7-8 : Remote Control
- [ ] RemoteStartTransaction
- [ ] RemoteStopTransaction
- [ ] Reset, ChangeAvailability

### Sprint 9-10 : Firmware Management
- [ ] UpdateFirmware
- [ ] GetDiagnostics
- [ ] Status notifications

### Sprint 11-12 : Features optionnelles
- [ ] Local Authorization
- [ ] Smart Charging
- [ ] Reservations

## 📈 Estimation Globale
- **Total** : 9-13 semaines
- **MVP** (Phases 1-2) : 5-7 semaines
- **Version complète** : 9-13 semaines
