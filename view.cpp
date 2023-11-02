// view.cpp
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

  tft.setCursor(20, 20); // Position pour "Tonnelle"
  tft.print("Tonnelles");
  tft.setCursor(20, 40); // Position pour "Tonnelle"
  tft.print("->");
  tft.setCursor(20, 60); // Position pour "Tonnelle"
  tft.print("Odysseum");

  for (int i=0; i<schedules.size(); i++)
  {
    tft.setCursor(20, 100*(i+1)); // Position pour 1er delai
    tft.print(String(schedules[i]));
  }

  /*
  tft.setCursor(20, 100); // Position pour 1er delai
  tft.print(String(schedules[0]));
  // tft.drawString(String(schedules[0]/60),  tft.width() / 2, tft.height() / 2 );

  tft.setCursor(20, 150); // Position pour 2eme delai
  tft.print(String(schedules[1]));
  Serial.println(String(schedules[1]));
  // tft.drawString(String(schedules[1]/60),  tft.width() / 2, tft.height() / 2 );
  */

  delay(10000);
}