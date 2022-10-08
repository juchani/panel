#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <ModbusIP_ESP8266.h>

#include "Arduino.h"

//VARIABLES
#define VT_PIN 34     //VOLTAJE GENERADO
#define AT_PIN 35     //CORRIENTE GENERADO
#define VT_CONSUMO 36 //VOLTAJE CONSUMO 
#define AT_CONSUMO 32 //CORRIENTE CONSUMO
#define adj 5  //  final de carrera ajuste 

#define ldr 17 //ldr digital 

int ang,enc;

//Modbus Registers Offsets
const int X_HREG = 100;
const int AZ_HREG = 101;
const int Z_HREG = 102;
const int G_HREG = 103;
const int H_HREG = 104;
const int ENC_HREG = 105;
const int ANG_HREG = 106;
const int Y_HREG = 107;
const int LDR_HREG = 108;
const int C_HREG = 109;
const int V_HREG = 110;
const int C_CONS_HREG = 111;
const int V_CONS_HREG = 112;
const int P_HREG=113;
int POT1=0;
int cc=0;
int x = 10, az = 360, z, g, h, old_az;

//ModbusIP object
ModbusIP mb;


long ts;
const char* ssid = "Osmanzonil";
const char* password = "Louie1234";
//Encoder
