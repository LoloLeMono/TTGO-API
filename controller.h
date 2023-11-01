// controller.h
#pragma once
#include "model.h"
#include "view.h"
#include <WebServer.h>

class Controller {
public:
  Model model;
  View view;
  WebServer& server;
  int LED_PIN;

  // Déclarations de fonctions liées au contrôleur
  Controller(WebServer&, int);
  void sendLedStatue();
  void handleLedStatue();
  void sendSensorsList();
  void sendJson();
};
