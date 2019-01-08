/* 
 *  This program is for valves installation (inital release tests,) 
 *  deintallation (release all liquid,) or other tests.
 *  
 *  Adjust the value of releaseTime and/or workingValve to suit different needs.
 *  
 */

//////////// VALVES ////////////
// set up constant pins
const int valvePins[] = {8, 9, 10, 11, 12, 13};

// set up variables for the working valve
int workingValve = 6;
int workingPin = 13;
int button = 2;

// set up release time
int releaseTime = 10000;

void setup() {
  Serial.begin(9600);
  Serial.println("initializing...");

  // set up pin modes
  pinMode(button, INPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(valvePins[i], OUTPUT);
  }
  pinMode(workingPin, OUTPUT);

  digitalWrite (button, HIGH);  // internal pull-up resistor

  //////////// valves ////////////
  for (int i = 0; i < 6; i++) {
    digitalWrite(valvePins[i], LOW); // switch all the valves OFF
  }
  Serial.println("starting...");
}

void loop() {
  if (digitalRead (button) == HIGH) {
    workingPin = valvePins[workingValve - 1];
    Serial.print(" pin no. "); Serial.print(workingPin);
    Serial.println();

    // switch on working pin
    digitalWrite(workingPin, HIGH); // switch the valve ON
    delay(releaseTime);
    digitalWrite(workingPin, LOW);
    Serial.println("valve OFF");

    // NOTE: TO RELEASE ONE DESIGNATED VALVE, comment this part and change the initial workingValve value
    if (workingValve < 6) {
      workingValve ++;
    } else {
      workingValve = 1;
    }

  }

}

