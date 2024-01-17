#pragma once
#include "sensor.h"
#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include <Button2.h>

class Model {
private:
  bool ledState;
  Sensor lumiere;
  std::list<Sensor> sensors;
  
  // Pin "DAC" = sorties analogiques pour générer des signaux analogiques.
  std::list<int> DAC_ports = {25, 26};

  // Pin "ADC" = entrées analogiques pour lectures analogiques.
  std::list<int> ADC_ports = {36, 37, 38, 39, 32, 33, 25, 26};

public:
  Button2 btn; // Bouton externe

  // Constructeur par défaut
  Model();

  // Initialisation du modèle
  void initialize();

  // Gestion de l'état de la LED
  void setLedState(bool state);
  bool getLedState();

  // Gestion des capteurs
  std::list<Sensor> getSensors();
  float getTemp(int pin);
  Sensor getLumiere();
  bool isSensorConnected(int pin);
  std::list<int> scanSensors();
};
