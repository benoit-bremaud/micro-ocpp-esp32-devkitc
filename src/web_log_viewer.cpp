#include <SPIFFS.h>
#include <WebServer.h>
#include "web_log_viewer.h"

extern WebServer server;

void handleRoot() {
    server.send(200, "text/html", "<h1>ESP32 Log Viewer</h1><p>Server is running!</p>");
}

void handleLogsList() {
    String html = "<h2>📄 All Files in SPIFFS</h2><ul>";

    File root = SPIFFS.open("/");
    if (!root) {
        server.send(500, "text/plain", "❌ Failed to open SPIFFS root directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        String name = file.name();
        html += "<li><a href=\"/logs" + name + "\">" + name + "</a></li>";
        file = root.openNextFile();
    }

    html += "</ul>";
    server.send(200, "text/html", html);
}

void handleLogFile() {
    String path = server.uri().substring(5);  // Remove "/logs" prefix
    if (path.isEmpty()) {
        server.send(400, "text/plain", "❌ No filename specified");
        return;
    }

    String fullPath = "/" + path;
    if (!SPIFFS.exists(fullPath)) {
        server.send(404, "text/plain", "❌ File not found");
        return;
    }

    File file = SPIFFS.open(fullPath, FILE_READ);
    if (!file) {
        server.send(500, "text/plain", "❌ Failed to open file");
        return;
    }

    String content;
    while (file.available()) {
        content += (char)file.read();
    }
    file.close();
    server.send(200, "text/plain", content);
}

namespace WebLogViewer {
    void setupServer() {
        server.on("/", handleRoot);
        server.on("/logs", HTTP_GET, handleLogsList);
        server.on("/logs/", HTTP_GET, handleLogFile); // support /logs/<filename>
        server.begin();
        Serial.println("[WebLogViewer] HTTP server started");
    }

    void handleClient() {
        server.handleClient();
    }
}
