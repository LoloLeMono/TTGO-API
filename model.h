// model.h
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

    // Pin "DAC" = sorties analogiques / générer des signaux analogiques.
    // Utiliser analogWrite pour générer des signaux de sortie analogiques.
    std::list<int> DAC_ports = {25, 26};
    int ledPin;

    // Pin "ADC" = sorties analogiques / lectures analogiques en utilisant analogRead.
    // Les valeurs analogiques sont généralement comprises entre 0 et 4095.
    std::list<int> ADC_ports = {36, 37, 38, 39, 32, 33, 25, 26};

    int temperaturePin;
    int lumierePin;
    
  public:
    Button2 btn;

    // Constructeur par défaut
    Model();

    // Constructeur avec initialisation personnalisée
    Model(bool initialState);

    // Déclarations de fonctions liées au modèle
    void initialize();
    void setLedState(bool state);
    bool getLedState();
    std::list<Sensor> getSensors();
    std::list<int> scanSensors();
    float getTemp(int pin);

    Sensor getLumiere();
    void printText(String txt);

    bool isSensorConnected(int pin);
};
