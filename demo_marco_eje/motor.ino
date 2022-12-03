void motor_1() {
  if (z > 29 && z < 91) {
    dato_rx = ( z * 1.4222222222) * 3; // Ajuste de 512 vueltas a los 360 grados
    // if(dato_rx>29 && dato_rx<91){
    while (dato_rx > numero_pasos && !digitalRead(ldr) == HIGH) { // Girohacia la izquierda en grados
      paso_izq();
      numero_pasos = numero_pasos + 1;

    }
    while (dato_rx < numero_pasos && !digitalRead(ldr) == HIGH) { // Giro hacia la derecha en grados
      while (dato_rx == 127 && !digitalRead(adj) == LOW) {
        paso_der();
        numero_pasos = 127;
      }
      if (!digitalRead(adj) == HIGH) {
        apagado();
        numero_pasos = 127;
      }
      else {
        paso_der();
      }
      numero_pasos = numero_pasos - 1;

    }
    while (dato_rx == 127 && !digitalRead(adj) == LOW) {
        paso_der();
        numero_pasos = 127;
      }

    apagado();         // Apagado del Motor para que no se caliente
  }
}

void paso_der() {        // Pasos a la derecha
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(retardo);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(retardo);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(retardo);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(retardo);
}

void paso_izq() {        // Pasos a la izquierda
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(retardo);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(retardo);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(retardo);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(retardo);
}

void apagado() {         // Apagado del Motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
