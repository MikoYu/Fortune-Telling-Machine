int stepCount = 0;

void stepperPattern() {
  // Pick a pattern program randomly
  pattern = int(random(1, patternCounts + 1));
  Serial.println(pattern);

  // Exert the randomly selected program
  switch (pattern) {
    case 1:
      // keep the mold static
      delay(5000);
      break;

    case 2:
      // spin clockwise for 3 rounds in 9 sec
      moldStepper.setSpeed(20);
      for (int i = 0; i < stepsPerRevolution * 3; i++) {
        moldStepper.step(1);

        //add shutdown func here
        if (digitalRead(stepperBtnPin) == HIGH) {
          break;
        }
      }
      break;

    case 3:
      // spin clockwise for 1 round, then counter-clockwise for 1 round, 4 sec each round
      moldStepper.setSpeed(15);
      for (int i = 0; i < stepsPerRevolution * 2; i++) {
        if (i < stepsPerRevolution) {
          moldStepper.step(1);
        } else {
          moldStepper.step(-1);
        }

        //add shutdown func here
        if (digitalRead(stepperBtnPin) == HIGH) {
          break;
        }
      }
      break;

    case 4:
      // - 0.5, + 1, - 0.5; 4 sec/roundd
      moldStepper.setSpeed(15);
      for (int i = 0; i < stepsPerRevolution * 2; i++) {
        if (i < stepsPerRevolution * 0.5) {
          moldStepper.step(1);
        } else if (i < stepsPerRevolution * 1.5) {
          moldStepper.step(-1);
        } else {
          moldStepper.step(1);
        }

        //add shutdown func here
        if (digitalRead(stepperBtnPin) == HIGH) {
          break;
        }
      }
      break;

  }

}

