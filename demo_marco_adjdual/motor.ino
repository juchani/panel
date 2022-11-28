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


  if (!digitalRead(ldr_) == HIGH  ) {
    dato_rx = ( z * 1.4222222222) * 40; // Ajuste de 512 vueltas a los 360 grados
    //uid16data[3]=dato_rx;
    while (dato_rx > numero_pasos && ang < 270) { // Girohacia la izquierda en grados
      paso_izq();
      rotary_loop();
      numero_pasos = numero_pasos + 1;
    }
    while (dato_rx < numero_pasos && ang > -86) { // Giro hacia la derecha en grados
      paso_der();
      rotary_loop();
      numero_pasos = numero_pasos - 1;
    }
  }
  apagado();         // Apagado del Motor para que no se caliente
}

void motor_2() {
  if (y > 29 && y < 91) {
    dato_rx_ = ( y * 1.4222222222) * 3; // Ajuste de 512 vueltas a los 360 grados
    // if(dato_rx>29 && dato_rx<91){
    while (dato_rx_ > numero_pasos_ && !digitalRead(ldr_) == HIGH) { // Girohacia la izquierda en grados
      paso_izq_();
      numero_pasos_ = numero_pasos_ + 1;
    }
    while (dato_rx_ < numero_pasos_ && !digitalRead(ldr_) == HIGH) { // Giro hacia la derecha en grados
      while (dato_rx_ == 127 && !digitalRead(FC_) == LOW) {
        paso_der_();
        numero_pasos_ = 127;
      }
      if (!digitalRead(FC_) == HIGH) {
        apagado_();
        numero_pasos_ = 127;
      }
      else {
        paso_der_();
      }
      numero_pasos_ = numero_pasos_ - 1;

    }
    while (dato_rx_ == 127 && !digitalRead(FC_) == LOW) {
        paso_der_();
        numero_pasos_ = 127;
      }

    apagado_();         // Apagado del Motor para que no se caliente
  }
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

void paso_der_() {        // Pasos a la derecha
  digitalWrite(in1_, LOW);
  digitalWrite(in2_, LOW);
  digitalWrite(in3_, HIGH);
  digitalWrite(in4_, HIGH);
  delay(retardo_);
  digitalWrite(in1_, LOW);
  digitalWrite(in2_, HIGH);
  digitalWrite(in3_, HIGH);
  digitalWrite(in4_, LOW);
  delay(retardo_);
  digitalWrite(in1_, HIGH);
  digitalWrite(in2_, HIGH);
  digitalWrite(in3_, LOW);
  digitalWrite(in4_, LOW);
  delay(retardo_);
  digitalWrite(in1_, HIGH);
  digitalWrite(in2_, LOW);
  digitalWrite(in3_, LOW);
  digitalWrite(in4_, HIGH);
  delay(retardo_);
}

void paso_izq_() {        // Pasos a la izquierda
  digitalWrite(in1_, HIGH);
  digitalWrite(in2_, HIGH);
  digitalWrite(in3_, LOW);
  digitalWrite(in4_, LOW);
  delay(retardo_);
  digitalWrite(in1_, LOW);
  digitalWrite(in2_, HIGH);
  digitalWrite(in3_, HIGH);
  digitalWrite(in4_, LOW);
  delay(retardo_);
  digitalWrite(in1_, LOW);
  digitalWrite(in2_, LOW);
  digitalWrite(in3_, HIGH);
  digitalWrite(in4_, HIGH);
  delay(retardo_);
  digitalWrite(in1_, HIGH);
  digitalWrite(in2_, LOW);
  digitalWrite(in3_, LOW);
  digitalWrite(in4_, HIGH);
  delay(retardo_);
}

void apagado_() {         // Apagado del Motor
  digitalWrite(in1_, LOW);
  digitalWrite(in2_, LOW);
  digitalWrite(in3_, LOW);
  digitalWrite(in4_, LOW);
}
