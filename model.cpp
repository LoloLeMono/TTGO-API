// model.cpp
#include "model.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <HTTPClient.h> // pour ESP32

Model::Model(){}

void Model::initialize() {
  // Initialisation du modèle
  ledState = false;
  //btn = btn(35);
  sensors.push_back(Sensor("lumiere", 0.0, 36.0));
}

void Model::setLedState(bool state) {
  // Mettre à jour l'état de la LED dans le modèle
  ledState = state;
}

bool Model::getLedState() {
  // Obtenir l'état actuel de la LED
  return ledState;
}

std::list<Sensor> Model::getSensors() {
  return this->sensors;
}

float Model::getTemp(int pin) {
  int analogValue = analogRead(pin);
  float R1 = 10000.0; // résistance fixe
  float T0 = 25.0 + 273.15;
  float R0 = 10000.0; // Résistance du thermistor à T0
  float B = 3950.0; // Coefficient B

  float Vout = analogValue * 3.3 / 4095.0;
    
  float RT = ((R1 * 3.3) / Vout) - R1;
  
  // Utilisation de la formule de Steinhart-Hart
  float lnRT = log(RT / R0);

  float tempK = 1.0 / ((1.0 / T0) + (1.0 / B) * lnRT);
  
  float tempC = tempK - 273.15;

  return tempC;
}

Sensor Model::getLumiere(){
  return this->lumiere;
}

bool Model::isSensorConnected(int pin) {
  int value = analogRead(pin); // ou digitalRead pour les signaux numériques
  // Remplacer 0 et 1023 par les valeurs attendues pour un capteur connecté
  return (value > 0); 
}

std::list<int> Model::scanSensors() {
    std::list<int> detectedSensors;
    for (int pin : ADC_ports) {
        if (isSensorConnected(pin)) {
            Serial.println("Capteur détecté sur la broche " + String(pin));
            detectedSensors.push_back(pin); // Ajouter le pin à la liste
        } else {
            Serial.println("Aucun capteur sur la broche " + String(pin));
        }
    }
    return detectedSensors;
}