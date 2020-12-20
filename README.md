# IoT-Home Automation

This project is all about connecting home appliances to our phone through internet

## Table of Content
1. Abstract
2. Components Used
3. Guide to install Code

## Abstarct
Nowadays due to the advancements in technologies, people started using smart gadgets in their daily life. In this home automation system, I have built an android application to control the basic home appliances like lights and fans. In addition to this, It is also enabled with a smart alarm system, in which we can continuously monitor the temperature and humidity of the house through our android application. The whole communication process is handled by the Microcontroller (NodeMCU), which is Wi-Fi enabled.  DHT11 sensor is used for measuring temperature and humidity. The data sending and receiving between the mobile application and the microcontroller is done via google-firebase.

## Components Used
The components used in this project are:
* MicroController (Node MCU)
* Humidity and Temperature Sensor (DHT11 Sensor)
* Smoke Sensor (MQ2 Sensor)
* Relays
* DC Motor (as Fan)
* AC Bulb

## Guide to install Code
Follow the Following steps to properly intsall the code into the MicroController
1. Install the below mentioned Libraries
  * ESP8266WiFi
  * FirebaseArduino
  * DHT
2. Creat your Firebase Account
3. Open the code file "HOME_AUTOMATION.ino"
4. Make the changes according to the commments mentioned in the code and fill the details.
5. make the connections.
6. Install the Android Applictaion.

That's it your *IoT based Home Automation System* is ready and you can operate it from anywhere in the world provided your phone and the microcontroller are connected to internet.
