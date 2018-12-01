/*
   Nov 18 Sunday
   - neopixel added to the system, tests ongoing

   in need:

   buttons for servo & stepper:
   - similar debounce function as neopixel

   stepper (6 - 12V):
   - more pattern variations.
   - need pulling up?

   solenoid valves (12V):
   - direct connection okay; not yet tested with arduino

*/

//////////// setting up the servo ////////////

#include <Servo.h>
Servo myservo;
const int servoPin = 12;
const int servoBtnPin = 4;

// set up defult constants (ms per round; stop speed for writeMicroseconds)
const int turnTime = 1600;
const int stopSpeed = 1415;

// for forced shutdown
bool servoShutdown = false;

// setting up time variables for multitasking
unsigned long ldrPreviousMillis = 0;
const long ldrInterval = 50;
unsigned long servoPreviousMillis = 0;
unsigned long currentMillis;
unsigned long deltaMillis;

// the ldrs for home locating; (the cell + 10K pulldown)
const int servoLdrPin = A0;
int servoLdrReading;
const int servoLdrThreshold = 260;

// the rotatry encoder
const int outputA = 6;
const int outputB = 7;
int rtCounter = 0;
int aState;
int aLastState;

//////////// setting up the stepper ////////////

#include <Stepper.h>
const int stepperBtnPin = 3;

// set up defult constants (steps per revolution)
const int stepsPerRevolution = 200;

// stepper/driver on pin 8, 9, 10, 11
Stepper moldStepper(stepsPerRevolution, 8, 9, 10, 11);

//////////// setting up the neopixel ////////////

// in another separate program in this version for stable power supply

//#include <Adafruit_NeoPixel.h>
//const int pixelPin = 5;
//const int pixelCount = 60;
//const int pixelBtnPin = 4;
//
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, pixelPin, NEO_GRB + NEO_KHZ800);
//// Parameter 3 = pixel type flags, add together as needed:
////   NEO_RGB     Pixels are wired for RGB bitstream
////   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
////   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
////   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
//
//// for case/style control
//bool pixelBtnLastState = HIGH;
//bool pixelBtnState;
//int showType = 0;
//int pos = 0, dir = 1;

//////////// other setups ////////////

// for random seed
const int seedPin = A5;



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
  //pinMode(pixelBtnPin, INPUT_PULLUP);

  // initial readings
  // use the input on A5 as random seed, to make the selection seem more "random"
  randomSeed(analogRead(seedPin));
  // read the initial state of its outputA
  aLastState = digitalRead(outputA);

  //strip.begin();
  //strip.show(); // Initialize all pixels to 'off'

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


//  // Get current button state.
//  pixelBtnState = digitalRead(pixelBtnPin);
//  // Check if state changed from high to low (button press).
//  if (pixelBtnState == LOW && pixelBtnLastState == HIGH) {
//    // Short delay to debounce button.
//    delay(20);
//    // Check if button is still low after debounce.
//    pixelBtnState = digitalRead(pixelBtnPin);
//    if (pixelBtnState == LOW) {
//      colorWipe(strip.Color(0, 0, 0), 0);
//      pixelStartShow(showType);
//      showType++;
//      if (showType > 4) {
//        showType = 0;
//      }
//    }
//  }
//  
//  // Set the last button state to the old state.
//  pixelBtnLastState = pixelBtnState;

}

