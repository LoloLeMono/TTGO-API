// controller.cpp
#include "controller.h"
#include "model.h"
#include "sensor.h"
#include "view.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <HTTPClient.h> // pour ESP32

Controller::Controller(WebServer& s, int ledPin) : server(s), LED_PIN(ledPin) {}

// Fonction d'envoi de l'état de la led
void Controller::sendLedStatue() {
  StaticJsonDocument<200> doc;
  doc["LED"] = this->model.getLedState() ? "ON" : "OFF";

  String jsonStr;
  serializeJson(doc, jsonStr);

  server.send(200, "application/json", jsonStr);
}

// Fonction d'envoi de l'état de la température
void Controller::sendTempValue() {
  StaticJsonDocument<200> doc;
  float temperature = model.getTemp(32);

  char str[256]; 
  sprintf(str, "%.2f", temperature);

  doc["TEMP"] = str;
  String jsonStr;
  serializeJson(doc, jsonStr);

  server.send(200, "application/json", jsonStr);
}

// Fonction d'envoi de l'état de la lumiere
void Controller::sendLumValue() {
  StaticJsonDocument<200> doc;
  int analogValue = analogRead(36);

  char str[256]; 
  sprintf(str, "%ld", analogValue);

  doc["LUM"] = str;
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

/*
void Controller::sendSensorsList() {
  
  // Obtient la liste des pins avec des capteurs détectés
  std::list<int> detectedPins = model.scanSensors();

  // Créez un document JSON
  DynamicJsonDocument doc(200);

  // Crée un tableau JSON
  JsonArray sensorArray = doc.createNestedArray("sensors");

  // Boucle pour remplir la liste du Json
  for (int pin : detectedPins) {
    // Obtenez le capteur correspondant au pin
    Sensor sensor = model.getSensorByPin(pin); // Supposant que cette méthode existe

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
*/

/*
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
*/

void Controller::sendSensorsList()
{
  model.scanSensors();
}

void Controller::sendJson() {
  StaticJsonDocument<200> doc;
  doc["LED"] = model.getLedState() ? "ON" : "OFF";

  String jsonStr;
  serializeJson(doc, jsonStr);

  server.send(200, "application/json", jsonStr);
}

String Controller::apiTamCall()
{
  // Effectuer la requête HTTP
  HTTPClient http;
  String url = "https://montpellier-tam-api.vercel.app/api/query?route_short_name=15&stop_name=TONNELLES&trip_headsign=ODYSSEUM";

  http.begin(url); // Commencer la requête HTTP
  int httpResponseCode = http.GET(); // Effectuer la requête GET

  String payload = http.getString(); // Obtenir la réponse de l'API

  http.end(); // Terminer la requête HTTP

  return payload;
}

bool Controller::getShowSchedules()
{
  return this->showSchedules;
}

void Controller::setShowSchedules(bool state)
{
  this->showSchedules = state;
}

long Controller::calculLum()
{

}