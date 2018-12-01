// to randomly select a pattern
int pattern;
int patternCounts = 4; // change counts here

// for forced shutdown
bool stepperShutdown = false;

void stepperProcess() {
  Serial.println("pattern process starts");
  stepperPattern();
  Serial.println("pattern process done");
  Serial.println();
  delay(500);
}

//////////// other functions ///////////

void stepperPattern() {
  // Pick a pattern program randomly
  pattern = int(random(1, patternCounts + 1));
  Serial.println(pattern);
  stepperShutdown = false;

  // Exert the randomly selected program
  switch (pattern) {
    case 1:
      // keep the mold static untill full; turn a little and turn back to notify
      stepperRotation(20, 0.1, 1);
      stepperRotation(20, 0.1, -1);
      break;

    case 2:
      // spin clockwise for 3 rounds in 9 sec
      stepperRotation(20, 3, 1);
      break;

    case 3:
      // spin clockwise for 1 round, then counter-clockwise for 1 round, 4 sec each round
      stepperRotation(15, 1, 1);
      stepperRotation(15, 1, -1);
      break;

    case 4:
      // - 0.5, + 1, - 0.5; 4 sec/roundd
      stepperRotation(15, 0.5, -1);
      stepperRotation(15, 1, 1);
      stepperRotation(15, 0.5, -1);
      break;

  }

}

void stepperRotation(int stepperSpeed, float stepperRounds, int stepperSteps) {

  if (stepperShutdown == true) {
    Serial.println("following process terminated");
  } else {

    moldStepper.setSpeed(stepperSpeed);
    for (int i = 0; i < stepsPerRevolution * stepperRounds; i++) {

      //////////// cases to stop the stepper ////////////
      // can be shutdown immediately during the process (only after i = 25 for stability)
      if (i > 25 && digitalRead(stepperBtnPin) == HIGH) {
        stepperShutdown = true;
      }

      if (stepperShutdown == true) {
        Serial.println("forced shutdown");
        break;
      }

      //////////// rotation ////////////
      moldStepper.step(stepperSteps);

    }
  }
}


