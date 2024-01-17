#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <Button2.h>
#include <math.h>

#include "model.h"
#include "view.h"
#include "controller.h"

// Déclaration des objets
Model model;
View view;
TFT_eSPI tft = TFT_eSPI(135, 240); // Configuration de l'écran TFT
WebServer server(80);              // Serveur Web sur le port 80
Controller controller(server, 26);

// Paramètres du mode AP (Point d'Accès)
const char *AP_SSID = "TTGO-Config";
const char *AP_PASSWORD = "12345678";

void setupWiFiAPMode() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.println("Mode AP démarré");
    Serial.print("IP du point d'accès: ");
    Serial.println(WiFi.softAPIP());
}

void handleWiFiConfig() {
    server.on("/config", HTTP_POST, []() {
        String WIFI_SSID = server.arg("ssid");
        String WIFI_PASSWORD = server.arg("password");

        if (WIFI_SSID.length() > 0 && WIFI_PASSWORD.length() > 0) {
            server.send(200, "text/plain", "Configuration reçue, tentative de connexion...");
            delay(1000); // Un délai de 100 millisecondes

            WiFi.mode(WIFI_STA);
            WiFi.begin(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str());

            unsigned long startTime = millis();
            while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
                delay(500);
                Serial.print(".");
            }

            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("\nConnecté au Wi-Fi !");
                Serial.print("Adresse IP : ");
                Serial.println(WiFi.localIP());
            } else {
                Serial.println("\nÉchec de la connexion. Retour en mode AP.");
                WiFi.mode(WIFI_AP);
            }
        } else {
            server.send(400, "text/plain", "Données SSID ou mot de passe manquantes.");
        }
    });
}

void setupServerEndpoints() {
  server.on("/led", HTTP_GET, [&controller]() { controller.sendLedStatue(); });
  server.on("/sensors", HTTP_GET, [&controller]() { controller.sendSensorsList(); });
  server.on("/led", HTTP_POST, [&controller]() { controller.handleLedStatue(); });
  server.on("/sensor/lum", HTTP_GET, [&controller]() { controller.sendLumValue(); });
  server.on("/sensor/temp", HTTP_GET, [&controller]() { controller.sendTempValue(); });
}

void setup() {
    Serial.begin(115200);
    pinMode(controller.LED_PIN, OUTPUT);

    setupWiFiAPMode();
    handleWiFiConfig();

    model.initialize();
    view.setup();
    controller.setShowSchedules(true);

    model.btn.setPressedHandler([](Button2 & b) {
        Serial.println("Button cliqué");
        controller.setShowSchedules(!controller.getShowSchedules());
    });

    setupServerEndpoints();
    server.begin();
    Serial.println("Serveur HTTP démarré");
}

void loop() {
    if (controller.getShowSchedules()) {
        server.handleClient();
        view.printShedules(controller.apiTamCall());
    }
    // Ajoutez ici d'autres fonctions qui doivent être exécutées dans la boucle loop
}