void servoFindhome() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= ldrInterval) {
    previousMillis = currentMillis;

    // read ldr data
    servoLdrReading = analogRead(servoLdrPin);

    Serial.print("servo ldr reading = ");
    Serial.println(servoLdrReading);

    // check if need to go back to home position (A: sol no.1; B: sol no. 5)
    if (servoLdrReading > ldrThreshold) {
      for (int servoTimer = 0; servoTimer < 2000; servoTimer += 100) {
        myservo.write(0);
        delay(50);
        myservo.writeMicroseconds(stopSpeed);
        delay(50);

        servoLdrReading = analogRead(servoLdrPin);
        Serial.print("servo ldr reading = ");
        Serial.println(servoLdrReading);

        if (servoLdrReading <= ldrThreshold) {
          Serial.println("servo back home");
          break;
        }
      }
    }

    else {
      Serial.println("servo already at home");
    }

  }
}

