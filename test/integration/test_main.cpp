// test/integration/test_main.cpp
// Ce fichier permet à PlatformIO de détecter et exécuter les tests d'intégration.
#include <Arduino.h>
#include <unity.h>
#include "test_system.cpp"

// Déclarez ici les prototypes de vos fonctions de test si besoin
extern void test_esp32_basic_functions();

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_esp32_basic_functions);
    // Ajoutez ici vos RUN_TEST si vous avez des fonctions de test dans ce dossier
    UNITY_END();
}

void loop() {}
