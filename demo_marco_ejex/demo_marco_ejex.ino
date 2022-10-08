#include "libb.h"
TaskHandle_t Task1;
int res;
int in4 = 27;
int in3 = 33;
int in2 = 25;
int in1 = 26;
int retardo = 3;        // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;            // valor recibido en grados
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor
String leeCadena;       // Almacena la cadena de datos recibida

void tcp0code( void * pvParameters );
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  //////////////DUAL CORE////////////

  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  ///////////CONFIGURACION IP/////////
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress ip(192, 168,0,23);
  WiFi.setSleep(false);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  otta ();


  mb.server();    //Start Modbus IP
  // Add SENSOR_IREG register - Use addIreg() for analog Inputs

  ////////ENCODER//////////
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  bool circleValues = false;
  rotaryEncoder.setBoundaries(-1000, 3000, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  rotaryEncoder.disableAcceleration();                    //acceleration is now enabled by default - disable if you dont need it
  //////////CONFIGURACION M1
  pinMode(in1, OUTPUT);    // Pin 11 conectar a IN4
  pinMode(in2, OUTPUT);    // Pin 10 conectar a IN3
  pinMode(in3, OUTPUT);     // Pin 9 conectar a IN2
  pinMode(in4, OUTPUT);     // Pin 8 conectar a IN1
  /////////////////////////
  mb.addHreg(X_HREG);
  mb.addHreg(AZ_HREG);
  mb.addHreg(Z_HREG);
  mb.addHreg(G_HREG);
  mb.addHreg(H_HREG);
  mb.addHreg(ENC_HREG);
  mb.addHreg(ANG_HREG);
  mb.addHreg(Y_HREG);
  mb.addHreg(LDR_HREG);
  mb.addHreg(C_HREG);
  mb.addHreg(V_HREG);
  mb.addHreg(C_CONS_HREG);
  mb.addHreg(V_CONS_HREG);
  mb.addHreg(PINI_HREG);
  ts = millis();
  old_az = az;
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (old_az != az ) {
    calculo();
    old_az = az;

  }

  rotary_loop();
  motor_1();
  az = mb.Hreg(AZ_HREG);
  x = ang;

}
void adj(){
  if(enc==400){
    numero_pasos=5119;
  }
  if(enc==198){
    numero_pasos=2559;
  }
  if(enc==601){
    numero_pasos=7679;
  }
}
void calculo() {
  if(az<90&&old_az>270){
    z=az;
  }
  else if ((az - x) > 270) {
    g = 360 - az;
    if (abs(g) >= 2) {

      z = az - 360;

    }
  }

  else if (x < 0) {
    g = az - 360;
    if ((abs(g) - abs(x)) >= 2) {
      z = az - 360;
    }
  }
  else if ((abs(az) - abs(x)) <= -2 || (abs(az) - abs(x)) >= 2) {
    z = az;
  }
}
