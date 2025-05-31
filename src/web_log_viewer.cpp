#include "web_log_viewer.h"
#include <WiFi.h>

using namespace WebLogViewer;

// Crée une instance globale du serveur sur le port 80
static WebServer server(80);

// Gestionnaire pour la racine "/"
void handleRoot() {
    server.send(200, "text/html", "<h1>ESP32 Log Viewer</h1><p>Server is running!</p>");
}

void WebLogViewer::setupServer() {
    // Configure les routes
    server.on("/", handleRoot);

    // Démarre le serveur
    server.begin();
    Serial.println("[WebLogViewer] HTTP server started");
}

void WebLogViewer::handleClient() {
    server.handleClient();
}
