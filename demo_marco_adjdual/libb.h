#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <ModbusIP_ESP8266.h>
#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"

//VARIABLES
#define VT_PIN 34      //VOLTAJE GENERADO
#define AT_PIN 35      // CORRIENTE GENERADO
#define VT_CONSUMO 36  //VOLTAJE
#define AT_CONSUMO 39  //CORRIENTE DE PLACA
#define FC_ 16         //  final de carrera ajuste
#define ldr_ 17        //ldr digital

//eje x
int enc;
int ang;

//direcciones de registro Modbus
const int X_HREG = 100;
const int AZ_HREG = 101;      //eje x
const int Z_HREG = 102;       //
const int G_HREG = 103;       //
const int H_HREG = 104;       //
const int ENC_HREG = 105;     //
const int ANG_HREG = 106;     ///
const int Y_HREG = 107;       //eje y
const int LDR_HREG = 108;     //
const int C_HREG = 109;       //corriente generado
const int V_HREG = 110;       //voltaje generado
const int C_CONS_HREG = 111;  //corriente de consumo
const int V_CONS_HREG = 112;  //voltaje consumo
const int PINI_HREG = 113;  //reg de posicion inicial

int POT1 = 0;
int cc = 0;
int p_inicial;
int x = 10, y = 0, az = 360, z, g, h, old_az;

//Modbus ip Objeto
ModbusIP mb;


long ts;
const char* ssid = "Osmanzonil";
const char* password = "Louie1234";

//Encoder
#define ROTARY_ENCODER_A_PIN 23
#define ROTARY_ENCODER_B_PIN 22
#define ROTARY_ENCODER_BUTTON_PIN 13
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 1

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

void rotary_loop() {
  if (rotaryEncoder.encoderChanged()) {
    Serial.print("Value: ");
    Serial.println(rotaryEncoder.readEncoder());
    enc = rotaryEncoder.readEncoder();

    ang = map(rotaryEncoder.readEncoder(), 0, 1606, 1, 360);
    // if(){

    // }
  }
  if (rotaryEncoder.isEncoderButtonClicked()) {
    //     rotary_onButtonClick();
  }
}

void IRAM_ATTR readEncoderISR() {
  rotaryEncoder.readEncoder_ISR();
}
