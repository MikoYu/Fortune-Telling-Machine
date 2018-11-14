/*
   Nov 13 Tuesday
   - got two motors work on the same UNO board;

   both:
   - need sensors for locating:
      - servo turns depend on the time it costs -> positions are not precise;
      - no home positions, can't calibrate.
   - replace delay functions.
   - need mechanisms to shutdown while running; still, keep only one motor running at a time.

   servo (6V / 7.2V):
   - not stable each time at the beginning; need to figure out why.
   - may change a smarter way to rotate to its target (to take shorter time.)

   stepper (6 - 12V):
   - more pattern variations.

   solenoid valves (12V):
   - haven't tested yet

*/

#include <Servo.h>
#include <Stepper.h>

// set up the buttons
const int servoBtnPin = 2;
const int stepperBtnPin = 3;

// set up the ldrs for home locating; the cell + 10K pulldown
const int servoLdrPin = A0;
const int stepperLdrPin = A1;
int servoLdrReading, servoLdrReading;

//////////// setting up the servo ////////////

Servo myservo;

//time for a whole round; not precise when scaling down
#define TURN_TIME 1600

// for random liquid selection
int solA, solB, solAforB;
const int solCounts = 8;

// home position of A and B; constant right now
int homeA = 0;
int homeB = 4;
// if defining current positions of A & B, posB = (posA + 4) % 8

// to calculate turning direction and time; all distances are depended on A
int distanceA, distanceB, distanceBack;
int turnTimeA, turnTimeB, turnTimeBack;

//////////// setting up the stepper ////////////

const int stepsPerRevolution = 200;
Stepper moldStepper(stepsPerRevolution, 8, 9, 10, 11);

// counters for home locating / shutdown
int stepCountHome = 0;
int stepCountPattern = 0;

// to randomly select a pattern
int pattern;
int patternCounts = 4; // change counts here

//////////// setting up multitasking ////////////
unsigned long previousMillis = 0;
const long ldrInterval = 60;

//////////// start running ////////////

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  Serial.println("starts working");

  // make the buttons' pin an input
  pinMode(servoBtnPin, INPUT);
  pinMode(stepperBtnPin, INPUT);
  pinMode(servoLdrPin, INPUT);
  pinMode(stepperLdrPin, INPUT);

  // servo info
  myservo.attach(6);
  // Initially the servo must be stopped
  myservo.writeMicroseconds(1415);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= sensorInterval) {
    previousMillis = currentMillis;

    // read ldr data
    servoLdrReading = analogRead(servoLdrPin);
    stepperLdrReading = analogRead(stepperLdrPin);
    Serial.print("servo ldr reading = ");
    Serial.println(servoLdrReading);
    Serial.print("stepper ldr reading = ");
    Serial.println(stepperLdrReading);


    // machine process

    servoProcess();
    stepperProcess();

  }

}

