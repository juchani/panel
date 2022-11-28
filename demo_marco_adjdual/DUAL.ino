///dual core
//los esp32 pueden trabajar en dos tareas de forma simultanea
//esta funcion se encarga de actualizar el registro modbus
//y recibir informacion desde la rpi(raspberry pi)
void Task1code(void* pvParameters) {
  while (1) {
    ArduinoOTA.handle();             //protocolo otta (actualizacion de codigo por red)
    mb.task();                       //actualiza los registros a un panel modbus
    az = mb.Hreg(AZ_HREG);           //actualiza az (eje x)
    x = mb.Hreg(X_HREG);             //actualiza x (angulo a ir)
    p_inicial = mb.Hreg(PINI_HREG);  //actualiza la posicion inicial(mayor a 50)
    y = mb.Hreg(Y_HREG);             //actualiza eje Y
    if (p_inicial > 50) {            //si la posicion inicial es mayor a 50 az=90 (eje x)
      az = 90;
    }

    //cada dos segundos
    if (millis() > ts + 200) {
      ts = millis();
      ///////CALIBRACIONES DE SENSOR DE VOLTAJE-CORRIENTE
      int vv = map(analogRead(VT_PIN), 0, 2733, 0, 116);  //voltaje map(analogRead(VT_PIN), 0, valor_a_mod, 0, voltaje_fijo)
      cc = map(analogRead(AT_PIN), 0, 97, 0, 170);        //corriente (ma) map(analogRead(VT_PIN), 0, valor_a_mod, 0, corriente fija_fija)

      int VC = map(analogRead(VT_CONSUMO), 0, 840, 0, 61);  //voltaje map(analogRead(VT_PIN), 0, valor_a_mod, 0, voltaje_fijo)
      int AC = map(analogRead(AT_CONSUMO), 0, 97, 0, 170);  //corriente (ma) map(analogRead(VT_PIN), 0, valor_a_mod, 0, corriente fija_fija)
      //Actualizacion de registros Modbus
      mb.Hreg(X_HREG, x);
      mb.Hreg(AZ_HREG, az);
      mb.Hreg(Z_HREG, z);
      mb.Hreg(G_HREG, g);
      mb.Hreg(H_HREG, numero_pasos);
      mb.Hreg(ENC_HREG, enc);
      mb.Hreg(ANG_HREG, ang);
      mb.Hreg(LDR_HREG, !digitalRead(ldr_));
      mb.Hreg(Y_HREG, y);
      mb.Hreg(PINI_HREG, p_inicial);
      /// si el voltaje y la corriente es mayor a 0 actualiza el reguistro modbus
      if (cc > 0 && vv > 0) {
        float a = vv / 10;
        float b = cc / 1000;
        POT1 = a * b;
        Serial.println(POT1);
        mb.Hreg(C_HREG, cc);
        mb.Hreg(V_HREG, vv);
        //        mb.Hreg(P_HREG, analogRead(VT_CONSUMO));
      }
      //actualiza el registro modbus
      mb.Hreg(C_CONS_HREG, AC);
      mb.Hreg(V_CONS_HREG, VC);
      //delay de 100 ms
      delay(100);
    }
  }
}
