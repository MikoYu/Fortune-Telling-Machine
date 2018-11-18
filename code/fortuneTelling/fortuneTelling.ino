/*
   Nov 17 Saturday
   - bugs fixed: servo/stepper shutting down functions and other minor problems

   in need:

   stepper (6 - 12V):
   - more pattern variations.
   - need pulling up?

   solenoid valves (12V):
   - direct connection okay; not yet tested with arduino

   neopixel
   - ongoing tests

*/

#include <Servo.h>
#include <Stepper.h>

//////////// setting up the inputs/outputs ////////////

// the motors
const int servoPin = 12;
// stepper's in later sections

// the buttons
const int servoBtnPin = 2;
const int stepperBtnPin = 3;

// the ldrs for home locating; (the cell + 10K pulldown)
const int servoLdrPin = A0;
int servoLdrReading;
const int servoLdrThreshold = 250;

// for random seed
const int seedPin = A5;

// the rotatry encoder
#define outputA 6
#define outputB 7
int rtCounter = 0;
int aState;
int aLastState;

//////////// setting up the servo ////////////

Servo myservo;

// set up defult constants (ms per round; stop speed)
#define TURN_TIME 1600
const int stopSpeed = 1415;

// for forced shutdown
bool servoShutdown = false;

// setting up multitasking
unsigned long ldrPreviousMillis = 0;
const long ldrInterval = 50;
unsigned long servoPreviousMillis = 0;
unsigned long currentMillis;
unsigned long deltaMillis;

//////////// setting up the stepper ////////////

// set up defult constants (steps per revolution)
const int stepsPerRevolution = 200;

// stepper/driver on pin 8, 9, 10, 11
Stepper moldStepper(stepsPerRevolution, 8, 9, 10, 11);


//////////// start running ////////////

void setup() {
  // initialize the serial port
  Serial.begin(9600);
  Serial.println("initializing...");

  // servo info
  myservo.attach(servoPin);
  // Initially the servo must be stopped
  myservo.writeMicroseconds(stopSpeed);

  // make the buttons/ldrs/rotary encoder pins as inputs
  pinMode(servoBtnPin, INPUT);
  pinMode(stepperBtnPin, INPUT);
  pinMode(servoLdrPin, INPUT);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);

  // initial readings
  // use the input on A5 as random seed, to make the selection seem more "random"
  randomSeed(analogRead(seedPin));
  // read the initial state of its outputA
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

