void Task1code( void * pvParameters ) {
  while (1) {
    ArduinoOTA.handle();
    mb.task();
    az = mb.Hreg(AZ_HREG);
    x = mb.Hreg(X_HREG);
    p_inicial=mb.Hreg(PINI_HREG);
    if(p_inicial>50){
      az=90;
    }
    //Read each two seconds
    if (millis() > ts + 2000) {
      ts = millis();
      if (mb.Hreg(Y_HREG) > -1 && mb.Hreg(Y_HREG) < 100) {
        Serial2.println(mb.Hreg(Y_HREG));
      }
      int vv = map(analogRead(VT_PIN), 0, 2733, 0, 116);
      cc = map(analogRead(AT_PIN), 0, 97, 0, 170);
      int VC = map(analogRead(VT_CONSUMO), 0, 2733, 0, 116);
      int AC = map(analogRead(AT_CONSUMO), 0, 97, 0, 170);

      //Setting raw value (0-1024)
      mb.Hreg(X_HREG, x );
      mb.Hreg(AZ_HREG, az);
      mb.Hreg(Z_HREG, z);
      mb.Hreg(G_HREG, g);
      mb.Hreg(H_HREG, numero_pasos);
      mb.Hreg(ENC_HREG, enc);
      mb.Hreg(ANG_HREG, ang);
      mb.Hreg(LDR_HREG, analogRead(39));
      mb.Hreg(PINI_HREG,p_inicial);
      if (cc > 0 && vv > 0) {
        float a = vv / 10;
        float b = cc / 1000;
        POT1 = a * b;
        Serial.println(POT1);
        mb.Hreg(C_HREG, cc);
        mb.Hreg(V_HREG, vv);
      }
      mb.Hreg(C_CONS_HREG,AC);
      mb.Hreg(V_CONS_HREG,  VC);

    }

    delay(10);

  }

}
