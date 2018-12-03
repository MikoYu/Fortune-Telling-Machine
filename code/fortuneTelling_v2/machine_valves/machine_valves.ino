const int valvePins[] = {8, 9, 10, 11, 12, 13};

int workingValve = 1;
int workingPin = 8;
int pushButton = 2;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(valvePins[i], OUTPUT);
  }
  pinMode(workingPin, OUTPUT);
  pinMode(pushButton, INPUT);
  Serial.begin(9600);
}

void loop() {

  // read the state of the button and check if it is pressed
  if (digitalRead(pushButton) == HIGH) {

    workingValve = int(random(1, 7));
    Serial.print("valve no. "); Serial.print(workingValve); Serial.print(" ON");
    workingPin = valvePins[workingValve - 1];
    Serial.print(" pin no. "); Serial.print(workingPin);
    Serial.println();
    digitalWrite(workingPin, HIGH); // switch the valve ON
    delay (6500);

    /*
    // loop by order for test
    if (workingValve < 6) {
      workingValve ++;
    } else {
      workingValve = 1;
    }
    Serial.print("next valve no. "); Serial.println(workingValve);
    */

  } else {

    // ramp down the motor speed
    digitalWrite(workingPin, LOW); // switch the valve OFF
    Serial.println("valve OFF");
    //delay (500);
  }

  delay(1);        // delay in between reads for stability
}
