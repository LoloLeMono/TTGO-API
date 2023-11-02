// view.h
#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

class View {
private:
  
public:
  TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

  // Constructeur par défaut
  View();
  
  // Déclarations de fonctions liées à la vue
  void setup();
  void displayLedState(bool state);

  void printShedules(String data);
};