const int valvePins[] = {8, 9, 10, 11, 12, 13};
const int pushButton = 2;

int workingValve = 0;
//int randomValve = 0;

void setup() {
  // define the in/out-put pins
  for (int i = 0; i < 6; i++) {
    pinMode(valvePins[i + 8], OUTPUT);
  }
  pinMode(pushButton, INPUT);

  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {

  // read the state of the button and check if it is pressed
  if (digitalRead(pushButton) == HIGH) {
    //    randomValve = int(rand(8, 14));
    //    workingValve = randomValve;
    
    digitalWrite(valvePins[workingValve], HIGH); // switch the valve ON
    Serial.print("valve no."); Serial.print(workingValve); Serial.println("ON");
    delay (6500);
    workingValve ++;

  } else {
    for (int i = 0; i < 6; i++) {
      digitalWrite(valvePins[i + 8], LOW); // all valves OFF
    }
    Serial.println("valves OFF");
    //delay (500);
  }

  delay(1);        // delay in between reads for stability
}
