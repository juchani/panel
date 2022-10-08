#include "libb.h"
TaskHandle_t Task1;
int res;
int in4 = 32;
int in3 = 33;
int in2 = 25;
int in1 = 26;
int retardo = 3;        // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;            // valor recibido en grados
int numero_pasos = 7;   // Valor en grados donde se encuentra el motor
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
  IPAddress ip(192, 168, 0, 66);
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
  mb.server();
  /////////////////////////
  mb.addHreg(C_HREG);
  mb.addHreg(V_HREG);
  mb.addHreg(C_CONS_HREG);
  mb.addHreg(V_CONS_HREG);
  ts = millis();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  mb.task();

  if (millis() > ts + 2000) {
    ts = millis();

    int vv = map(analogRead(VT_PIN), 0, 2733, 0, 116);
    int cc = map(analogRead(AT_PIN), 0, 97, 0, 170);

    if (cc > 0 && vv > 0) {
      mb.Hreg(C_HREG, cc);
      mb.Hreg(V_HREG, vv);
    }


    //mb.Hreg(C_CONS_HREG,VC);
    //mb.Hreg(V_CONS_HREG, AC);

  }

  delay(10);



}
