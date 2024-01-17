#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class Sensor
{
  private:
    String name;
    long value;
    int pin;
    
  public:
    // Constructeur par défaut
    Sensor();

    // Constructeur avec initialisation personnalisée
    Sensor(String name, long value, int pin);

    String getName();
    long getValue();
    int getPin();

    void scanPin();
};
