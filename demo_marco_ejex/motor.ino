void motor_1() {
  int liim = 500;
  if (p_inicial > 50) {
    while (ang < 0) {
      paso_izq();
      rotary_loop();
      numero_pasos = numero_pasos + 1;
      p_inicial = 0;
      az = 90;
      liim = -1;
    }
    
    p_inicial = 0;
    if (old_az != az ) {
      calculo();
      old_az = az;

    }

    dato_rx = ( z * 1.4222222222) * 40; // Ajuste de 512 vueltas a los 360 grados
    //uid16data[3]=dato_rx;
    while (dato_rx > numero_pasos) { // Girohacia la izquierda en grados
      paso_izq();
      rotary_loop();
      numero_pasos = numero_pasos + 1;
    }
    while (dato_rx < numero_pasos) { // Giro hacia la derecha en grados
      paso_der();
      rotary_loop();
      numero_pasos = numero_pasos - 1;
    }
  }


  if (analogRead(ldr) > liim  ) {
    dato_rx = ( z * 1.4222222222) * 40; // Ajuste de 512 vueltas a los 360 grados
    //uid16data[3]=dato_rx;
    while (dato_rx > numero_pasos && ang < 270) { // Girohacia la izquierda en grados
      paso_izq();
      rotary_loop();
      numero_pasos = numero_pasos + 1;
    }
    while (dato_rx < numero_pasos && ang > -88) { // Giro hacia la derecha en grados
      paso_der();
      rotary_loop();
      numero_pasos = numero_pasos - 1;
    }
  }
  apagado();         // Apagado del Motor para que no se caliente
}

void paso_der() {        // Pasos a la derecha
  adj();
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
  adj();
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
