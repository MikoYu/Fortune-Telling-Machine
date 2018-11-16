void servoFindhome() {

  if (currentMillis - ldrPreviousMillis >= ldrInterval) {
    ldrPreviousMillis = currentMillis;

    // read ldr data
    servoLdrReading = analogRead(servoLdrPin);

    Serial.print("servo ldr reading = ");
    Serial.println(servoLdrReading);

    // check if need to go back to home position (A: sol no.1; B: sol no. 5)
    if (servoLdrReading > servoLdrThreshold) {

      servoPreviousMillis = currentMillis;

      for (int servoTimer = 0; servoTimer < 2000; servoTimer += 100) {
        if (currentMillis - servoPreviousMillis < 50) {
          myservo.write(0);
        } else if (currentMillis - servoPreviousMillis < 100) {
          myservo.write(stopSpeed);
        } else {
          servoPreviousMillis = currentMillis;
        }

        servoLdrReading = analogRead(servoLdrPin);
        Serial.print("servo ldr reading = ");
        Serial.println(servoLdrReading);

        if (servoLdrReading <= servoLdrThreshold) {
          Serial.println("servo back home");
          break;
        }

        if (digitalRead(servoBtnPin) == HIGH) {
          myservo.write(stopSpeed);
          break;
        }

      }

    }

    else {
      Serial.println("servo already at home");
    }

  }
}

