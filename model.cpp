// model.cpp
#include "model.h"

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
  std::list<int> buff;

  for (int i=0; i<this->DAC_ports.size(); i++)
  {
    // Scanner le pin DAC_ports[i] stocker le résultat dans sensors[]
  }

  for (int i=0; i<this->ADC_ports.size(); i++)
  {
    // Scanner le pin ADC_ports[i] stocker le résultat dans sensors[]
  }
}