#include <Arduino.h>
#include <ArduinoJson.h>
#include "sensor.h"
#include "model.h"

Sensor::Sensor(){}

Sensor::Sensor(String n, long v, int p) : name(n), value(v), pin(p) {}

String Sensor::getName()
{
  return this->name;
}

long Sensor::getValue()
{
  return this->value;
}

int Sensor::getPin()
{
  return this->pin;
}