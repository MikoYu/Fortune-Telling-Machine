/*
 * Nov 13 Tuesday
 * - got two motors work on the same UNO board;
 * 
 * both: 
 * - need sensors for locating:
 *    - servo turns depend on the time it costs -> positions are not precise;
 *    - no home positions, can't calibrate.
 * - replace delay functions.
 * - need mechanisms to shutdown while running; still, keep only one motor running at a time.
 * 
 * servo (6V / 7.2V):
 * - not stable each time at the beginning; need to figure out why.
 * - may change a smarter way to rotate to its target (to take shorter time.)
 * 
 * stepper (6 - 12V):
 * - more pattern variations.
 * 
 * solenoid (12V):
 * - haven't tested yet
 * 
 */

#include <Servo.h>
#include <Stepper.h>

// set up the buttons
const int servoBtnPin = 2;
const int stepperBtnPin = 3;

//////////// setting up the servo ////////////

Servo myservo;

//time for a whole round; not precise when scaling down
#define TURN_TIME 1600

// for random liquid selection
int solA, solB, solAforB;
int solCounts = 8;

// previous position of A and B
int preA = 1;
int preB = 5;

// to calculate turning direction and time
int distanceA, distanceB, distanceBack;
int turnTimeA, turnTimeB, turnTimeBack;

//////////// setting up the stepper ////////////

const int stepsPerRevolution = 200;
Stepper moldStepper(stepsPerRevolution, 8, 9, 10, 11);

// to randomly select a pattern
int pattern;
int patternCounts = 4; // change counts here


//////////// start running ////////////

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  Serial.println("starts working");

  // make the buttons' pin an input
  pinMode(servoBtnPin, INPUT);
  pinMode(stepperBtnPin, INPUT);

  // servo info
  myservo.attach(6);
  // Initially the servo must be stopped
  myservo.writeMicroseconds(1415);

  // better to have a "home" position (with a sensors; photocell, for eg.)
  // for the servo: calibrate to home position (A: sol no.1; B: sol no. 5)

}

void loop() {

  //////////// servo ////////////

  // read the state of the button and check if it is pressed
  if (digitalRead(servoBtnPin) == HIGH) {
    Serial.println("servo button on");

    // pick the liquid for A and B randomly
    solA = int(random(1, solCounts + 1));
    solB = int(random(1, solCounts + 1));
    Serial.print("A: "); Serial.println(solA);
    Serial.print("B: "); Serial.println(solB);

    // calculate turning direction and time
    distanceA = solA - preA;
    if (solB < 5) {
      solAforB = solB + 4;
    } else {
      solAforB = solB - 4;
    }
    distanceB = solAforB - solA;
    distanceBack = preA - solAforB;
    Serial.print("A': "); Serial.println(solAforB);
    Serial.print("distance A: "); Serial.println(distanceA);
    Serial.print("distance B: "); Serial.println(distanceB);
    Serial.print("distance Back: "); Serial.println(distanceBack);

    turnTimeA = TURN_TIME / 8 * abs(distanceA);
    turnTimeB = TURN_TIME / 8 * abs(distanceB);
    turnTimeBack = TURN_TIME / 8 * abs(distanceBack);

    // turn to get liquid A
    if (solA == 1) {
      // Keep still for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }
    else {
      // turn clockwise to get liquid A
      myservo.write(0);
      delay(turnTimeA);
      // stop for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);     
    }

    // the solenoid dispsenses liquid A

    // turn to get liquid B
    if (distanceB == 0) {
      // leep still for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }
    else if (distanceB > 0) {
      // turn clockwise to get liquid B
      myservo.write(0);
      delay(turnTimeB);
      // stop for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    } else {
      // turn clockwise to get liquid B
      myservo.write(180);
      delay(turnTimeB);
      // stop for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }

    // the solenoid dispsenses liquid B

    // turn to home position and stop
    myservo.write(180);
    delay(turnTimeBack);
    // stop for 5 sec
    myservo.writeMicroseconds(1415);
    delay(5000);
    Serial.println("liquid part done");

  }
  else {
    //Serial.println("pushButton off");
  }

  // delay in between reads for stability
  delay(1);

  //////////// stepper ////////////

  // read the state of the button and check if it is pressed
  if (digitalRead(stepperBtnPin) == HIGH) {
    Serial.println("stepper button on");

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

  // delay in between reads for stability
  delay(1);

}

