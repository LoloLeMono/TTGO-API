#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>

#include "model.h"
#include "view.h"
#include "controller.h"

// Initialisation des objets
Model model;
View view;

TFT_eSPI tftf = TFT_eSPI(135, 240); // Invoke custom library

#define WIFI_SSID "Bbox-46D5F041"
#define WIFI_PASSWORD "sdS7RDTR33awhGKHAT"

WebServer server(80);

Controller controller(server, 26);

void setup() {
  Serial.begin(115200);
  pinMode(controller.LED_PIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialisation du modèle et de la vue
  model.initialize();
  view.setup();

  // Configuration des routes Web
  server.on("/led", HTTP_GET, [&controller]() { controller.sendLedStatue(); });
  server.on("/sensors", HTTP_GET, [&controller]() { controller.sendSensorsList(); });  // Ajoutez cette ligne

  server.on("/led", HTTP_POST, [&controller]() { controller.handleLedStatue(); });


  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  view.printShedules(controller.apiTamCall());
}