/*
   Nov 14 Wednesday
   - used photocells to find home position
   - servo with precise locating funcs with a rotary encoder
   - stepper can be shutdown

   in need:

   
   servo (6V / 7.2V):
   - need mechanisms to be shutdown while running
   - not stable each time at the beginning; need to figure out why.
   - may change a smarter way to rotate to its target (to take shorter time.)

   stepper (6 - 12V):
   - more pattern variations.
   - need pulling up?

   solenoid valves (12V):
   - haven't tested yet
   - need pulling up

*/

#include <Servo.h>
#include <Stepper.h>

// set up the buttons
const int servoBtnPin = 2;
const int stepperBtnPin = 3;

// set up the ldrs for home locating; the cell + 10K pulldown
const int servoLdrPin = A0;
const int stepperLdrPin = A1;
int servoLdrReading, stepperLdrReading;
const int servoLdrThreshold = 250;
const int stepperLdrThreshold = 350;

// set up the rotatry encoder
#define outputA 6
#define outputB 7

int rtCounter = 0;
int aState;
int aLastState;

//////////// setting up the servo ////////////

Servo myservo;

//time for a whole round; not precise when scaling down
#define TURN_TIME 1600
const int stopSpeed = 1415;
const int liquidDispensingTime = 7000;

// for random liquid selection
int solA, solB, solAforB;
const int solCounts = 8;

// home position of A and B; constant right now
int homeA = 0;
int homeB = 4;
// if defining current positions of A & B, posB = (posA + 4) % 8

// to calculate turning direction and time; all distances are depended on A
int distanceA, distanceB, distanceBack;
int turnDegreeA, turnDegreeB, turnDegreeBack;

//////////// setting up the stepper ////////////

const int stepsPerRevolution = 200;
Stepper moldStepper(stepsPerRevolution, 8, 9, 10, 11);

// to randomly select a pattern
int pattern;
int patternCounts = 4; // change counts here

//////////// setting up multitasking ////////////

unsigned long previousMillis = 0;
const long ldrInterval = 50;

//////////// start running ////////////

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  Serial.println("initializing...");

  // servo info
  myservo.attach(12);
  // Initially the servo must be stopped
  myservo.writeMicroseconds(stopSpeed);

  // make the buttons/ldrs/rotary encoder pins as inputs
  pinMode(servoBtnPin, INPUT);
  pinMode(stepperBtnPin, INPUT);
  pinMode(servoLdrPin, INPUT);
  pinMode(stepperLdrPin, INPUT);
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);

  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);

  Serial.println("starts working");

}

void loop() {

  // read the state of the button and check if it is pressed
  if (digitalRead(servoBtnPin) == HIGH) {
    Serial.println("servo button on");
    servoProcess();
  }
  delay(1); // delay in between reads for stability

  // read the state of the button and check if it is pressed
  if (digitalRead(stepperBtnPin) == HIGH) {
    Serial.println("stepper button on");
    stepperProcess();
  }
  delay(1); // delay in between reads for stability


}

