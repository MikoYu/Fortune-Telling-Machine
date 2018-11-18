void servoFindhome() {

  // read ldr data
  servoLdrReading = analogRead(servoLdrPin);

  Serial.print("servo ldr reading = ");
  Serial.println(servoLdrReading);

  // check if need to go back to home position (A: sol no.1; B: sol no. 5)
  if (servoLdrReading > servoLdrThreshold) {
    currentMillis = millis();
    servoPreviousMillis = currentMillis;
    deltaMillis = currentMillis - servoPreviousMillis;

    for (int i = 0; i < 300; i += 1) {

      //////////// cases to stop the servo ////////////
      if (i > 20 && digitalRead(servoBtnPin) == HIGH) {
        servoShutdown = true;
        Serial.println("forced shutdown");
      }

      if (deltaMillis >= 5000) {
        servoShutdown = true;
        Serial.println("servo can't find home");

      }

      if (servoShutdown == true) {
        myservo.writeMicroseconds(stopSpeed);
        Serial.println("servo stops");
        break;
      }

      //////////// finding home ////////////
      currentMillis = millis();
      deltaMillis = currentMillis - servoPreviousMillis;

      if (deltaMillis % 100 < 50) {
        myservo.write(0);
      } else if (deltaMillis % 100 < 100) {
        myservo.writeMicroseconds(stopSpeed);
      }

      servoLdrReading = analogRead(servoLdrPin);
      Serial.print("servo ldr reading = ");
      Serial.println(servoLdrReading);

      if (servoLdrReading <= servoLdrThreshold) {
        Serial.println("servo back home");
        myservo.writeMicroseconds(stopSpeed);
        break;
      }

    }

  }

  else {
    Serial.println("servo already at home");
  }

}

