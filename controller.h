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
  int LUM_PIN;
  bool showSchedules;

  // Déclarations de fonctions liées au contrôleur
  Controller(WebServer&, int);
  bool getShowSchedules();
  void setShowSchedules(bool state);
  void sendLedStatue();
  void sendLumValue();
  void sendTempValue();
  void handleLedStatue();
  void sendSensorsList();
  void sendJson();

  String apiTamCall();
  long calculLum();
};
