// model.h
#pragma once
#include "sensor.h"
#include <Arduino.h>
#include <list>

class Model {
  private:
    bool ledState;
    std::list<Sensor> sensors;

    // Pin "DAC" = sorties analogiques / générer des signaux analogiques.
    // Utiliser analogWrite pour générer des signaux de sortie analogiques.
    std::list<int> DAC_ports = {25, 26};

    // Pin "ADC" = sorties analogiques / lectures analogiques en utilisant analogRead.
    // Les valeurs analogiques sont généralement comprises entre 0 et 4095.
    std::list<int> ADC_ports = {2, 15, 13, 12, 36, 39, 32, 33, 25, 26, 27};
    
  public:
    // Constructeur par défaut
    Model();

    // Constructeur avec initialisation personnalisée
    Model(bool initialState);

    // Déclarations de fonctions liées au modèle
    void initialize();
    void setLedState(bool state);
    bool getLedState();
    std::list<Sensor> getSensors();
    void scanSensors();
};
