void stepperFindhome() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= ldrInterval) {
    previousMillis = currentMillis;

    // read ldr data
    stepperLdrReading = analogRead(stepperLdrPin);

    Serial.print("stepper ldr reading = ");
    Serial.println(stepperLdrReading);

    // check if need to go back to home position (A: sol no.1; B: sol no. 5)
    if (stepperLdrReading > stepperLdrThreshold) {
      for (int stepperCounts = 0; stepperCounts < 20; stepperCounts ++) {
        moldStepper.setSpeed(20);
        moldStepper.step(stepsPerRevolution / 20);

        stepperLdrReading = analogRead(stepperLdrPin);
        Serial.print("stepper ldr reading = ");
        Serial.println(stepperLdrReading);

        if (stepperLdrReading <= stepperLdrThreshold) {
          Serial.println("stepper back home");
          break;
        }
      }
    }

    else {
      Serial.println("stepper already at home");
    }

  }

}

