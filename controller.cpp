// controller.cpp
#include "controller.h"
#include "model.h"
#include "sensor.h"
#include "view.h"
#include <WebServer.h>
#include <ArduinoJson.h>

Controller::Controller(WebServer& s, int ledPin) : server(s), LED_PIN(ledPin) {}

// Fonction d'envoi de l'état de la led
void Controller::sendLedStatue() {
  StaticJsonDocument<200> doc;
  doc["LED"] = this->model.getLedState() ? "ON" : "OFF";

  String jsonStr;
  serializeJson(doc, jsonStr);

  server.send(200, "application/json", jsonStr);
}

// Fonction de gestion de la led
void Controller::handleLedStatue() {
  String request = server.arg("plain");
  DynamicJsonDocument doc(200);
  DeserializationError error = deserializeJson(doc, request);

  if (error) {
    server.send(400, "application/json", "Bad Request");
  } else {
    model.setLedState(doc["LED"] == "ON");
    digitalWrite(LED_PIN, model.getLedState() ? HIGH : LOW); // Change l'état de la led
    sendJson();
  }
}

void Controller::sendSensorsList() {
  
  // Met a jour la liste des sensors
  model.scanSensors();

  std::list<Sensor> sensors = model.getSensors();
  
  // Créez un document JSON
  DynamicJsonDocument doc(200);

  // Crée un tableau JSON
  JsonArray sensorArray = doc.createNestedArray("sensors");

  // Boucle pour remplir la liste du Json
  for (Sensor& sensor : sensors) {
    JsonObject sensorJson = sensorArray.createNestedObject();

    sensorJson["name"] = sensor.getName();
    sensorJson["value"] = sensor.getValue();
    sensorJson["pin"] = std::to_string(sensor.getPin());
  }

  // Créer une chaîne de caractères JSON à partir du document
  String jsonStr;
  serializeJson(doc, jsonStr);

  // Envoi le json
  server.send(200, "application/json", jsonStr);
}

void Controller::sendJson() {
  StaticJsonDocument<200> doc;
  doc["LED"] = model.getLedState() ? "ON" : "OFF";

  String jsonStr;
  serializeJson(doc, jsonStr);

  server.send(200, "application/json", jsonStr);
}