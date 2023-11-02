// model.cpp
#include "model.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <HTTPClient.h> // pour ESP32

Model::Model(){}

void Model::initialize() {
  // Initialisation du modèle
  ledState = false;
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

// Scanner les ports de l'esp et les stocker dans la liste "sensors"
void Model::scanSensors()
{

  // Scanner le pin DAC_ports[i] stocker le résultat dans sensors[] (write possible)
  for (int i=0; i<this->DAC_ports.size(); i++)
  {
    /*
    int lecture = analogRead(DAC_ports[i]);

    if (detecterCapteurTemperature(lecture)) {
      Serial.print("Capteur de température LM35 détecté sur le pin ");
      Serial.print(DAC_ports[i]);
      Serial.println(); // Pour ajouter un saut de ligne
    } else if (detecterCapteurLumiere(lecture)) {
      Serial.println("Capteur de lumiere détecté sur le pin ");
      Serial.print(DAC_ports[i]);
      Serial.println(); // Pour ajouter un saut de ligne
    } else {
      Serial.println("Aucun capteur détecté sur le pin ");
      Serial.print(DAC_ports[i]);
      Serial.println(); // Pour ajouter un saut de ligne
    }

    delay(1000);
    */
  }

  // Scanner le pin ADC_ports[i] stocker le résultat dans sensors[]
  for (int i=0; i<this->ADC_ports.size(); i++)
  {
    /*
    int etatCapteur = digitalRead(ADC_ports[i]);

    if (etatCapteur == HIGH) {
      Serial.println("Le capteur est actif (HIGH).");
    } else {
      Serial.println("Le capteur est inactif (LOW).");
    }

    delay(1000);
    */
  }
}

bool Model::detecterCapteurTemperature(int valeur){
  // Plage de valeurs typiques pour un capteur LM35
  return (valeur >= 200 && valeur <= 800);
}

bool Model::detecterCapteurLumiere(int valeur){
  // Plage de valeurs typiques pour un capteur LM35
  return (valeur >= 200 && valeur <= 800);
}