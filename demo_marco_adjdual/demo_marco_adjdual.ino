//doble eje //
//ip:192, 168, 0, 3
#include "libb.h"      // incluye el archivo libb.h (incluido en la carpeta)
TaskHandle_t Task1;    // se crea una nueva tarea (para el segundo nucleo)
int retardo = 3;       // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;           // valor recibido en grados
int numero_pasos = 0;  // Valor en grados donde se encuentra el motor
String leeCadena;      // Almacena la cadena de datos recibida
//configuraciones de pines Motor 1
int in4 = 15;
int in3 = 2;
int in2 = 0;
int in1 = 4;
//configuraciones de pines Motor 2
int in4_ = 27;
int in3_ = 26;
int in2_ = 25;
int in1_ = 33;

int retardo_ = 3;         // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx_;             // valor recibido en grados
int numero_pasos_ = 384;  // Valor en grados donde se encuentra el motor
String leeCadena_;        // Almacena la cadena de datos recibida

void tcp0code(void* pvParameters);  //acceso a la funcion tcp0code (segundo nucleo)

void setup() {
  Serial.begin(9600);

  //////////////DUAL CORE////////////
  //configuracion del segundo nucleo
  xTaskCreatePinnedToCore(
    Task1code, /* Task function. */
    "Task1",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task1,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */
  ///////////CONFIGURACION IP/////////
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress ip(192, 168, 0, 3);      //configuracion de ip (revisar el tercer parametro)
  WiFi.setSleep(false);              // desactiva  el ahorro de energia (mejora la transmisión de datos)
  WiFi.mode(WIFI_STA);               // configura el esp32 en modo estación (se conecta la red)
  WiFi.config(ip, gateway, subnet);  //configura la ip
  WiFi.begin(ssid, password);        // inicia la coneccion a la red (revisar libb.h para cambiar de red)

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {  //crea un bucle en caso de no estar disponible se reinicia
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  otta();  // habilita la funcion otta (cargar el codigo por red) los detalles se encuentran en update_wifi.ino


  mb.server();  //inicia la coneccion modbus
  //////////CONFIGURACION M1
  pinMode(in1, OUTPUT);  // Pin 11 conectar a IN4
  pinMode(in2, OUTPUT);  // Pin 10 conectar a IN3
  pinMode(in3, OUTPUT);  // Pin 9 conectar a IN2
  pinMode(in4, OUTPUT);  // Pin 8 conectar a IN1
  //////////CONFIGURACION M2
  pinMode(in1_, OUTPUT);  // Pin 11 conectar a IN4
  pinMode(in2_, OUTPUT);  // Pin 10 conectar a IN3
  pinMode(in3_, OUTPUT);  // Pin 9 conectar a IN2
  pinMode(in4_, OUTPUT);  // Pin 8 conectar a IN1

  ////////ENCODER//////////
  rotaryEncoder.begin();                                   //inicia la configuracion del encoder (revisar libb.h para cambiar la configuracion)
  rotaryEncoder.setup(readEncoderISR);                     //se configura usando ISR(Interrupt service routines) interrupciones para que haga el conteo en todo momento
  bool circleValues = false;                               //desactiva el limitador y pueda usar numeros negativos
  rotaryEncoder.setBoundaries(-1000, 3000, circleValues);  //valor minimo, valor maximo,limitador
  rotaryEncoder.disableAcceleration();                     //como va a una velocidad constante no se requiere habilitar la aceleracion
  //////////CONFIGURACION M1
  pinMode(in1, OUTPUT);  // Pin 11 conectar a IN4
  pinMode(in2, OUTPUT);  // Pin 10 conectar a IN3
  pinMode(in3, OUTPUT);  // Pin 9 conectar a IN2
  pinMode(in4, OUTPUT);  // Pin 8 conectar a IN1
  //////////Registros  de Modbus (revisar libb.h para cambiar la configuracion de los registros)
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

  ts = millis();                   //genera un conador
  old_az = az;                     //variable para detectar si hay cambios en el eje x
  Serial.println(WiFi.localIP());  //imprime la ip del dispositivo
  pinMode(FC_, INPUT_PULLUP);      // configura el final de carrera en modo pullup(sin resistencias)
}

void loop() {
  motor_2();  //ejecuta la funcion motor_2 en el archivo motor.ino (eje Y)
              //detecta algun cambio en el eje x
              //hace los calculos para determinar el sentido de giro
  if (old_az != az) {
    calculo();
    old_az = az;
  }

  rotary_loop();          //actualiza las variables del encoder
  motor_1();              ////ejecuta la funcion motor_1 en el archivo motor.ino (eje x)
  az = mb.Hreg(AZ_HREG);  //actualiza el eje x en el registro de modbus
  x = ang;                // actualiza el angulo en en el eje x
}

//////funcion adj 
// realiza un set de pasos en los siguientes angulos:
//45,90,135 
void adj() {
  if (enc == 400) {
    numero_pasos = 5119;
    p_inicial = 0;
  }
  if (enc == 200) {
    numero_pasos = 2559;
  }
  if (enc == 600) {
    numero_pasos = 7679;
  }
}

//funcion calulo
//Realiza los calculos para determinar el sentido en el eje x
void calculo() {
  if (az < 90 && old_az > 270) {
    z = az;
  } else if ((az - x) > 181) {
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
  } else if ((abs(az) - abs(x)) <= -2 || (abs(az) - abs(x)) >= 2) {
    z = az;
  }
}
