void Task1code( void * pvParameters ) {
  while (1) {
    
    ArduinoOTA.handle();
    mb.task();
    az = mb.Hreg(AZ_HREG);
    x = mb.Hreg(X_HREG);
    //Read each two seconds
    if (millis() > ts + 200) {
      ts = millis();
      if (mb.Hreg(Y_HREG) > 29 && mb.Hreg(Y_HREG) < 100) {
        z = mb.Hreg(Y_HREG);
      }

      int vv = map(analogRead(VT_PIN), 0, 2733, 0, 116);
      cc = map(analogRead(AT_PIN), 0, 97, 0, 170);
      int VC = map(analogRead(VT_CONSUMO), 0, 760, 0, 35);
      int AC = map(analogRead(AT_CONSUMO), 0, 97, 0, 170);
      //Setting raw value (0-1024)
      mb.Hreg(X_HREG, x );
      mb.Hreg(AZ_HREG, az);
      mb.Hreg(Z_HREG, z);
      mb.Hreg(G_HREG, dato_rx);
      mb.Hreg(H_HREG, numero_pasos);
      mb.Hreg(ENC_HREG, analogRead(VT_CONSUMO));
      mb.Hreg(ANG_HREG, ang);
      mb.Hreg(LDR_HREG, analogRead(ldr));
      if (cc > 0 && vv > 0) {
        float a = vv / 10;
        float b = cc / 1000;
        POT1 = a * b;
        Serial.println(POT1);
        mb.Hreg(C_HREG, cc);
        mb.Hreg(V_HREG, vv);
        mb.Hreg(P_HREG, analogRead(VT_CONSUMO));
      }
      
      mb.Hreg(C_CONS_HREG, AC);
      mb.Hreg(V_CONS_HREG, VC);
      
      
      delay(100);


    }



  }

}
