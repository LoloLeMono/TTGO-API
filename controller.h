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
  bool showSchedules;

  // Constructeur
  Controller(WebServer&, int);

  // Fonctions pour la gestion de l'état et des données
  void sendLedStatue();
  void sendLumValue();
  void sendTempValue();
  void handleLedStatue();
  void sendSensorsList();
  void sendJson();
  String apiTamCall();

  // Fonctions pour la gestion des états
  bool getShowSchedules();
  void setShowSchedules(bool state);
};