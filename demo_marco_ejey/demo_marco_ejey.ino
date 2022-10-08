#include "libb.h"
TaskHandle_t Task1;
int res;
int in1 = 15;
int in2 = 33;
int in3 = 25;
int in4 = 26;
int retardo = 3;        // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;            // valor recibido en grados
int numero_pasos = 384;   // Valor en grados donde se encuentra el motor
String leeCadena;       // Almacena la cadena de datos recibida

void tcp0code( void * pvParameters );
void setup() {
  Serial.begin(9600);
 
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
  IPAddress ip(192, 168,0,73);
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
  mb.addHreg(P_HREG);
  ts = millis();
  old_az = az;
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(adj,INPUT_PULLUP);
}

void loop() {
    motor_1();
 

}
