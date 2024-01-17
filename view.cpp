#include "view.h"
#include "model.h"
#include <vector>
#include <TFT_eSPI.h>
#include <Arduino.h>

View::View(){}

void View::setup() {
  // Initialisation de l'interface utilisateur
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
}

void View::displayLedState(bool state) {
  // Affichage de l'état de la LED dans l'interface utilisateur
}

void View::printShedules(String payload)
{
  const char* json = payload.c_str();

  DynamicJsonDocument doc(1024); // Créez un document JSON avec une capacité de 1024 octets

  // Analysez la réponse JSON
  deserializeJson(doc, json);

  String delay_sec;
  std::vector<String> schedules;

  // Accéder aux données "delay_sec" et les stocker
  const JsonArray& result = doc["result"];
  for (const JsonObject& item : result)
  {
    delay_sec = item["delay_sec"].as<String>();
    schedules.push_back(item["delay_sec"]);
  }

  tft.setRotation(1);

  tft.setCursor(10, 10);
  tft.print("Tonnelles");
  tft.setCursor(90, 10);
  tft.print("->");
  tft.setCursor(130, 10);
  tft.print("Odysseum");

  for (int i=0; i<schedules.size(); i++)
  {
    schedules[i] = secondsToMinuts(schedules[i]);
    tft.drawString(schedules[i], 8+(i*80), 50, 7);
  }

  delay(10000);
}

String View::secondsToMinuts(String s)
{
  int buff = s.toInt();
  buff = buff/60;
  //Serial.println(String(buff));

  return String(buff);
}