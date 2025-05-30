/**
* @file hardware_manager.cpp
* @brief Implémentation sécurisée du gestionnaire hardware
* 
* Issue: #62 - [INFRA] ESP32 Hardware Configuration
* Version avec toutes les constantes définies
*/

#include "hardware_manager.h"

HardwareManager::HardwareManager() {
    currentState = HW_STATE_INIT;
    lastMeasurementTime = 0;
    lastBlinkTime = 0;
    lastErrorBlinkTime = 0;
    blinkInterval = BLINK_INTERVAL_NORMAL;
    errorBlinkInterval = BLINK_INTERVAL_ERROR;
    statusLedState = false;
    errorLedState = false;
    blinkingEnabled = false;
    errorBlinkingEnabled = false;
    
    // Initialiser les mesures à zéro
    memset(&lastMeasurements, 0, sizeof(hardware_measurements_t));
    
    Serial.println("🔧 HardwareManager: Constructeur appelé");
}

HardwareManager::~HardwareManager() {
    Serial.println("🔧 HardwareManager: Destructeur appelé");
    stopBlinking();
}

bool HardwareManager::init() {
    Serial.println("🔧 Initialisation du gestionnaire hardware...");
    
    try {
        // Vérifier la mémoire disponible
        if (ESP.getFreeHeap() < 50000) {
            Serial.printf("❌ Mémoire insuffisante: %d bytes\n", ESP.getFreeHeap());
            return false;
        }
        
        // Initialisation GPIO
        Serial.println("   - Initialisation GPIO...");
        if (!initializeGPIO()) {
            Serial.println("❌ Erreur initialisation GPIO");
            return false;
        }
        
        // Initialisation des capteurs
        Serial.println("   - Initialisation capteurs...");
        if (!initializeSensors()) {
            Serial.println("❌ Erreur initialisation capteurs");
            return false;
        }
        
        // Auto-test
        Serial.println("🔍 Auto-test du hardware...");
        if (!runSelfTest()) {
            Serial.println("❌ Auto-test échoué");
            currentState = HW_STATE_ERROR;
            return false;
        }
        
        // Première mesure
        updateMeasurements();
        
        // Changer l'état
        currentState = HW_STATE_READY;
        
        Serial.printf("✅ Gestionnaire hardware initialisé (Heap: %d bytes)\n", ESP.getFreeHeap());
        return true;
        
    } catch (...) {
        Serial.println("❌ Exception lors de l'initialisation hardware");
        currentState = HW_STATE_ERROR;
        return false;
    }
}

void HardwareManager::loop() {
    unsigned long now = millis();
    
    try {
        // Mise à jour des mesures selon l'intervalle configuré
        if (now - lastMeasurementTime >= MEASUREMENT_INTERVAL) {
            updateMeasurements();
            lastMeasurementTime = now;
        }
        
        // Gestion du clignotement de la LED de statut
        if (blinkingEnabled && (now - lastBlinkTime >= blinkInterval)) {
            statusLedState = !statusLedState;
            digitalWrite(LED_STATUS_PIN, statusLedState);
            lastBlinkTime = now;
        }
        
        // Gestion du clignotement de la LED d'erreur
        if (errorBlinkingEnabled && (now - lastErrorBlinkTime >= errorBlinkInterval)) {
            errorLedState = !errorLedState;
            digitalWrite(LED_ERROR_PIN, errorLedState);
            lastErrorBlinkTime = now;
        }
        
        // Vérifier l'état du bouton
        checkButton();
        
    } catch (...) {
        Serial.println("❌ Exception dans HardwareManager::loop()");
        currentState = HW_STATE_ERROR;
        setErrorLed(true);
    }
}

hardware_state_t HardwareManager::getState() {
    return currentState;
}

// ============================================================================
// CONTRÔLE DES LEDs
// ============================================================================

void HardwareManager::setStatusLed(bool state) {
    statusLedState = state;
    blinkingEnabled = false; // Arrêter le clignotement
    digitalWrite(LED_STATUS_PIN, state);
}

void HardwareManager::setErrorLed(bool state) {
    errorLedState = state;
    errorBlinkingEnabled = false; // Arrêter le clignotement
    digitalWrite(LED_ERROR_PIN, state);
}

void HardwareManager::blinkStatusLed(uint32_t interval_ms) {
    blinkInterval = interval_ms;
    blinkingEnabled = true;
    lastBlinkTime = millis();
}

void HardwareManager::blinkErrorLed(uint32_t interval_ms) {
    errorBlinkInterval = interval_ms;
    errorBlinkingEnabled = true;
    lastErrorBlinkTime = millis();
}

void HardwareManager::stopBlinking() {
    blinkingEnabled = false;
    errorBlinkingEnabled = false;
    setStatusLed(false);
    setErrorLed(false);
}

// ============================================================================
// CONTRÔLE DU BUZZER
// ============================================================================

void HardwareManager::buzzer(uint32_t duration_ms) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration_ms);
    digitalWrite(BUZZER_PIN, LOW);
}

void HardwareManager::buzzerBeep(uint8_t count, uint32_t duration_ms) {
    for (uint8_t i = 0; i < count; i++) {
        buzzer(duration_ms);
        if (i < count - 1) {
            delay(duration_ms);
        }
    }
}

void HardwareManager::buzzerAlert() {
    // Pattern SOS: 3 courts, 3 longs, 3 courts
    for (int i = 0; i < 3; i++) { buzzer(100); delay(100); }
    delay(200);
    for (int i = 0; i < 3; i++) { buzzer(300); delay(100); }
    delay(200);
    for (int i = 0; i < 3; i++) { buzzer(100); delay(100); }
}

// ============================================================================
// LECTURE DES CAPTEURS
// ============================================================================

hardware_measurements_t HardwareManager::readMeasurements() {
    return lastMeasurements;
}

float HardwareManager::readCurrent(uint8_t phase) {
    #ifndef SIMULATION_MODE
    uint32_t pin = (phase == 1) ? CURRENT_SENSOR_L1_PIN : CURRENT_SENSOR_L2_PIN;
    uint32_t adc_reading = readADCAverage(pin);
    float voltage = adcToVoltage(adc_reading);
    float current = VOLTAGE_TO_CURRENT(voltage);
    return constrain_value(abs(current), 0.0f, ACS712_MAX_CURRENT);
    #else
    // Simulation: courant variable
    float base = (phase == 1) ? SIM_CURRENT_BASE : SIM_CURRENT_BASE * 0.8f;
    return base + (random(-200, 300) / 100.0);
    #endif
}

float HardwareManager::readVoltage() {
    #ifndef SIMULATION_MODE
    uint32_t adc_reading = readADCAverage(VOLTAGE_SENSOR_PIN);
    float voltage = adcToVoltage(adc_reading);
    return constrain_value(voltage * VOLTAGE_DIVIDER_RATIO, 0.0f, VOLTAGE_MAX);
    #else
    // Simulation: tension stable autour de 230V
    return SIM_VOLTAGE_BASE + (random(-50, 50) / 10.0);
    #endif
}

float HardwareManager::readTemperature() {
    #ifndef SIMULATION_MODE
    uint32_t adc_reading = readADCAverage(TEMP_SENSOR_PIN);
    float voltage = adcToVoltage(adc_reading);
    float temperature = VOLTAGE_TO_TEMP(voltage);
    return constrain_value(temperature, TEMP_THRESHOLD_LOW, TEMP_THRESHOLD_HIGH);
    #else
    // Simulation: température variable
    return SIM_TEMP_BASE + (random(-100, 150) / 10.0);
    #endif
}

float HardwareManager::calculatePower() {
    float current_total = lastMeasurements.current_l1 + lastMeasurements.current_l2;
    return lastMeasurements.voltage * current_total / 1000.0; // kW
}

bool HardwareManager::isButtonPressed() {
    return digitalRead(BUTTON_PIN) == LOW;
}

// ============================================================================
// DIAGNOSTIC ET TESTS
// ============================================================================

bool HardwareManager::runSelfTest() {
    Serial.println("   - Test LEDs...");
    if (!testLeds()) return false;
    
    Serial.println("   - Test buzzer...");
    if (!testBuzzer()) return false;
    
    Serial.println("   - Test capteurs...");
    if (!testSensors()) return false;
    
    Serial.println("✅ Auto-test réussi");
    return true;
}

bool HardwareManager::testLeds() {
    #ifndef SIMULATION_MODE
    // Test LED status
    digitalWrite(LED_STATUS_PIN, HIGH);
    delay(100);
    digitalWrite(LED_STATUS_PIN, LOW);
    
    // Test LED erreur
    digitalWrite(LED_ERROR_PIN, HIGH);
    delay(100);
    digitalWrite(LED_ERROR_PIN, LOW);
    #else
    Serial.println("   - [SIM] Test LEDs simulé");
    #endif
    
    return true;
}

bool HardwareManager::testBuzzer() {
    #ifndef SIMULATION_MODE
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    #else
    Serial.println("   - [SIM] Test buzzer simulé");
    #endif
    
    return true;
}

bool HardwareManager::testSensors() {
    #ifndef SIMULATION_MODE
    // Test lecture ADC
    uint32_t test1 = analogRead(CURRENT_SENSOR_L1_PIN);
    uint32_t test2 = analogRead(VOLTAGE_SENSOR_PIN);
    
    if (test1 == 0 && test2 == 0) {
        Serial.println("❌ Capteurs ADC non détectés");
        return false;
    }
    #else
    Serial.println("   - [SIM] Test capteurs ADC simulé");
    float current1 = readCurrent(1);
    float current2 = readCurrent(2);
    float voltage = readVoltage();
    float temperature = readTemperature();
    
    Serial.printf("     [SIM] Current1: %.2f A\n", current1);
    Serial.printf("     [SIM] Current2: %.2f A\n", current2);
    Serial.printf("     [SIM] Voltage: %.2f V\n", voltage);
    Serial.printf("     [SIM] Temperature: %.2f °C\n", temperature);
    #endif
    
    return true;
}

void HardwareManager::printDiagnostics() {
    Serial.println("🔧 ===== DIAGNOSTIC HARDWARE =====");
    Serial.printf("   État: %d\n", currentState);
    Serial.printf("   Heap libre: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("   Uptime: %lu ms\n", millis());
    
    hardware_measurements_t measurements = readMeasurements();
    Serial.printf("   Courant L1: %.2f A\n", measurements.current_l1);
    Serial.printf("   Courant L2: %.2f A\n", measurements.current_l2);
    Serial.printf("   Tension: %.2f V\n", measurements.voltage);
    Serial.printf("   Température: %.2f °C\n", measurements.temperature);
    Serial.printf("   Puissance: %.2f kW\n", measurements.power);
    Serial.printf("   Bouton: %s\n", measurements.button_pressed ? "PRESSÉ" : "RELÂCHÉ");
    Serial.println("🔧 ==============================");
}

// ============================================================================
// MÉTHODES PRIVÉES
// ============================================================================

bool HardwareManager::initializeGPIO() {
    #ifndef SIMULATION_MODE
    // Configuration des pins GPIO
    pinMode(LED_STATUS_PIN, OUTPUT);
    pinMode(LED_ERROR_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    // État initial
    digitalWrite(LED_STATUS_PIN, LOW);
    digitalWrite(LED_ERROR_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    #else
    Serial.println("   - [SIM] Initialisation GPIO limitée (mode simulation)");
    Serial.println("⚠️ MODE SIMULATION ACTIVÉ - Capteurs non connectés");
    #endif
    
    return true;
}

bool HardwareManager::initializeSensors() {
    #ifndef SIMULATION_MODE
    // Configuration des pins analogiques
    pinMode(CURRENT_SENSOR_L1_PIN, INPUT);
    pinMode(CURRENT_SENSOR_L2_PIN, INPUT);
    pinMode(VOLTAGE_SENSOR_PIN, INPUT);
    pinMode(TEMP_SENSOR_PIN, INPUT);
    
    // Configuration ADC
    analogReadResolution(ADC_RESOLUTION);
    analogSetAttenuation(ADC_11db); // Plage 0-3.3V
    #endif
    
    return true;
}

void HardwareManager::updateMeasurements() {
    try {
        lastMeasurements.timestamp = millis();
        lastMeasurements.current_l1 = readCurrent(1);
        lastMeasurements.current_l2 = readCurrent(2);
        lastMeasurements.voltage = readVoltage();
        lastMeasurements.temperature = readTemperature();
        lastMeasurements.power = calculatePower();
        lastMeasurements.button_pressed = isButtonPressed();
        
        // Calcul simple de l'énergie (approximation)
        static float last_power = 0;
        static unsigned long last_time = 0;
        
        unsigned long now = millis();
        if (last_time > 0) {
            float time_hours = (now - last_time) / 3600000.0;
            lastMeasurements.energy += (last_power + lastMeasurements.power) / 2.0 * time_hours;
        }
        
        last_power = lastMeasurements.power;
        last_time = now;
        
    } catch (...) {
        Serial.println("❌ Exception lors de la mise à jour des mesures");
    }
}

void HardwareManager::checkButton() {
    static bool lastButtonState = HIGH;
    static unsigned long lastDebounceTime = 0;
    
    bool buttonState = digitalRead(BUTTON_PIN);
    
    if (buttonState != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > 50) { // Debounce 50ms
        if (buttonState == LOW && lastButtonState == HIGH) {
            // Bouton pressé
            Serial.println("🔘 Bouton pressé");
            buzzer(100);
            
            // Changer d'état pour test
            if (currentState == HW_STATE_READY) {
                currentState = HW_STATE_CHARGING;
                blinkStatusLed(BLINK_INTERVAL_FAST);
            } else {
                currentState = HW_STATE_READY;
                blinkStatusLed(BLINK_INTERVAL_NORMAL);
            }
        }
    }
    
    lastButtonState = buttonState;
}
