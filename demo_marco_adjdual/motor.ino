void motor_1() {
//  int liim = 500;
  if (p_inicial > 50) {  //si la posicion inicial (Reg 113) es mayor a 50 (posicion inicial)
    while (ang < 0) {
      paso_izq();
      rotary_loop();
      numero_pasos = numero_pasos + 1;  //conteo de pasos
      p_inicial = 0;                    //setea la direccion (Reg 113) 
      az = 90;                          //setea el eje x a 90° 
  //    liim = -1;                        //
    }

    p_inicial = 0;
    if (old_az != az) {
      calculo();
      old_az = az;
    }

    dato_rx = (z * 1.4222222222) * 40;  // Ajuste de vueltas a 360 grados
    //uid16data[3]=dato_rx;
    while (dato_rx > numero_pasos) {  // Girohacia la izquierda en grados
      paso_izq();
      rotary_loop();                    //actualizacion del encoder
      numero_pasos = numero_pasos + 1;  // conteo de pasos
    }
    while (dato_rx < numero_pasos) {  // Giro hacia la derecha en grados
      paso_der();                      
      rotary_loop();                    //actualizacion del encoder
      numero_pasos = numero_pasos - 1;  // conteo de pasos
    }
  }


  if (!digitalRead(ldr_) == HIGH) { //si el LDR esta activo
    dato_rx = (z * 1.4222222222) * 40;  // Ajuste de vueltas a  grados
    //uid16data[3]=dato_rx;
    while (dato_rx > numero_pasos && ang < 270) {  // Girohacia la izquierda en grados
      paso_izq();
      rotary_loop();                    //actualizacion del encoder
      numero_pasos = numero_pasos + 1;  //conteo de pasos
    }
    while (dato_rx < numero_pasos && ang > -86) {  // Giro hacia la derecha en grados
      paso_der();
      rotary_loop();                    //actualizacion del encoder
      numero_pasos = numero_pasos - 1;  //conteo de pasos
    }
  }
  apagado();  // Apagado del Motor para que no se caliente
}

void motor_2() {
  if (y > 29 && y < 91) {
    dato_rx_ = (y * 1.4222222222) * 3;  // Ajuste de vueltas a grados
    // if(dato_rx>29 && dato_rx<91){
    while (dato_rx_ > numero_pasos_ && !digitalRead(ldr_) == HIGH) {  // Girohacia la izquierda en grados
      paso_izq_();
      numero_pasos_ = numero_pasos_ + 1;  //conteo de pasos
    }
//  EJE Y   
    while (dato_rx_ < numero_pasos_ && !digitalRead(ldr_) == HIGH) {  // Giro hacia la derecha en grados
//RUTINA PARA IR A POSICION INICIAL
//SI EL ANGULO ES 30° Y EL FINAL DE CARRERA NO ESTA PRESIONADO 
      while (dato_rx_ == 127 && !digitalRead(FC_) == LOW) {
        paso_der_();
        numero_pasos_ = 127;
      }
//SI EL FINAL DE CARRERA ESTA ACTIVADO
//SETEA A 30° AUTOMATICAMENTE Y APAGA EL MOTOR 
//EN CASO CONTRARIO GIRA HASTA SER ACTIVADO
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

    apagado_();  // Apagado del Motor para que no se caliente
  }
}


void paso_der() {  // Pasos a la derecha
  adj();//FUNCION ADJ (SETEO DE PASOS)
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

void paso_izq() {  // Pasos a la izquierda
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

void apagado() {  // Apagado del Motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void paso_der_() {  // Pasos a la derecha
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

void paso_izq_() {  // Pasos a la izquierda
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

void apagado_() {  // Apagado del Motor
  digitalWrite(in1_, LOW);
  digitalWrite(in2_, LOW);
  digitalWrite(in3_, LOW);
  digitalWrite(in4_, LOW);
}
