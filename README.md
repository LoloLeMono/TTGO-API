Projet IOT - TTGO Restfull API
========================

Voici le code source de notre projet de Master 2 dans le cadre de L'UE HAI912.
Le but de ce projet est de déployer une API sur un microcontrolleur TTGO afin de controller différents capteurs et une led.

Documentation
------------

* analogRead() : Lire des valeurs analogiques sur les broches analogiques étiquetées "ADC" ou "Touch" sur les cartes TTGO.

* analogWrite() : Générer des signaux analogiques sur les broches qui prennent en charge le PWM souvent étiquetées "DAC".

* digitalRead() : Les broches numériques renvoient soit HIGH (1) soit LOW (0) et sont généralement étiquetées comme "GPIO xx", où "xx" est le numéro de la broche. 

Installation
------------

### Manual installation

Shéma du cablage

Usage
---------------

* Une fois le cablage fais, vous pouvez brancher l'ESP avec le programme téléversé à l'interieur.
* Connectez vous au réseau "TTGO-Config" avec le mdp "12345678".
* Alternative test : Rentrez le SSID et le code de votre réseau wifi (en dur) dans le fichier "HAI912I-Projet" présent dans le projet.
* Grace à l'application (ou une simple requête http), vous pouvez envoyer le ssid et le mdp de votre réseau WiFi au TTGO.
* Vous pouvez désormais utiliser l'api pour interagir avec les capteurs.

## Routes Disponibles du Serveur

- **GET /led**
  - Renvoie l'état actuel de la LED.

- **GET /sensors**
  - Liste les capteurs disponibles.

- **POST /led**
  - Permet de changer l'état de la LED.

- **GET /sensor/lum**
  - Renvoie la valeur actuelle de luminosité du capteur.

- **GET /sensor/temp**
  - Renvoie la valeur actuelle de température du capteur.


Authors:
----------------

* Ryan BENGOUFA  <ryan.bengoufa@etu.umontpellier.fr>
* Lucas ROUQUAIROL  <lucas.rouquairol@etu.umontpellier.fr>