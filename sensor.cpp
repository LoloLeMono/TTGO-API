// sensor.cpp
#include <Arduino.h>
#include <ArduinoJson.h>
#include "sensor.h"
#include "model.h"

Sensor::Sensor(){}

Sensor::Sensor(String n, String v, int p) : name(n), value(v), pin(p) {}

String Sensor::getName()
{
  return this->name;
}

String Sensor::getValue()
{
  return this->value;
}

int Sensor::getPin()
{
  return this->pin;
}