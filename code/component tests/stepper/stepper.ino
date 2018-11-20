#include <Stepper.h>

// initialize info about the stepper
const int stepsPerRevolution = 200;
Stepper moldStepper(stepsPerRevolution, 8, 9, 10, 11);

// set up the button
const int stepperBtnPin = 3;

// to randomly select a pattern
int pattern;
int patternCounts = 4; // change counts here

void setup() {
  // initialize the serial port
  Serial.begin(9600);

  // make the pushbutton's pin an input:
  pinMode(stepperBtnPin, INPUT);

  // better to control a "home" position (with a sensor)

}

void loop() {

  // read the state of the button and check if it is pressed
  if (digitalRead(stepperBtnPin) == HIGH) {
    Serial.println("pushButton on");

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
        moldStepper.step(stepsPerRevolution * 3);
        delay(500);
        break;
      case 3:
        // spin clockwise for 1 round, then counter-clockwise for 1 round, 4 sec each round
        moldStepper.setSpeed(15);
        moldStepper.step(stepsPerRevolution);
        delay(500);
        moldStepper.step(-stepsPerRevolution);
        delay(500);
        break;
      case 4:
        // - 0.5, + 1, - 0.5; 4 sec/roundd
        moldStepper.setSpeed(15);
        moldStepper.step(stepsPerRevolution * -0.5);
        delay(500);
        moldStepper.step(stepsPerRevolution);
        delay(500);
        moldStepper.step(stepsPerRevolution * -0.5);
        delay(500);
        break;

    }

    // better to stop the motor if there's another button on
    // also need go back to "home" position when "forced shutdown"

    Serial.println("pattern part done");

  }
  else {
    //Serial.println("pushButton off");

  }

  delay(1);        // delay in between reads for stability

}

