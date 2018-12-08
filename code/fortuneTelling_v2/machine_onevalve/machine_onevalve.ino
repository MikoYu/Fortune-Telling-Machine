const int pushButton = 2;
int workingPin = 13;

void setup() {
  pinMode(workingPin, OUTPUT);
  pinMode(pushButton, INPUT);

  // use the input on A5 as random seed, to make the selection seem more "random"
  //randomSeed(analogRead(seedPin));
  
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pushButton) == HIGH) {
    Serial.println("valve on");

    digitalWrite(workingPin, HIGH); // switch the valve ON
    delay (6500);


 } else {

    // ramp down the motor speed
    digitalWrite(workingPin, LOW); // switch the valve OFF
    Serial.println("valve OFF");
    delay (500);
}

  //delay(1);        // delay in between reads for stability
}
