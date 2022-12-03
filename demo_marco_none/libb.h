#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <ModbusIP_ESP8266.h>
#include "Arduino.h"
//VARIABLES
#define VT_PIN 34  // VOLTAJE DE PANEL 
#define AT_PIN 35  // AMPERAJE DE PANEL
#define VT_CONSUMO 36 //VOLTAJE DE PLACA 
#define AT_CONSUMO 39 //CORRIENTE DE PLACA
//Modbus Registers Offsets

const int C_HREG = 109;
const int V_HREG = 110;
const int C_CONS_HREG = 111;
const int V_CONS_HREG = 112;


//ModbusIP object
ModbusIP mb;


long ts;
//const char* ssid = "Osmanzonil";
//const char* password = "Louie1234";
const char* ssid = "Esp32";
const char* password = "12345678";
