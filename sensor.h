// sensor.h
#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class Sensor
{
  private:
    String name;
    String value;
    int pin;
    
  public:
    // Constructeur par défaut
    Sensor();

    // Constructeur avec initialisation personnalisée
    Sensor(String name, String value, int pin);

    String getName();
    String getValue();
    int getPin();

    void scanPin();
};
