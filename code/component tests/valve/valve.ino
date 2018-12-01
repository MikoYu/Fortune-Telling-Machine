int solenoidPin = 9; //solenid valve pin
int pushButton = 2;


void setup() {
  pinMode(solenoidPin, OUTPUT);
  pinMode(pushButton, INPUT);
  Serial.begin(9600);
}

void loop() {

  // read the state of the button and check if it is pressed
  if (digitalRead(pushButton) == HIGH) {
    digitalWrite(solenoidPin, HIGH); // switch the valve ON
    Serial.println("valve ON");
    //delay (500);
  } else {

    // ramp down the motor speed
    digitalWrite(solenoidPin, LOW); // switch the valve OFF
    Serial.println("valve OFF");
    //delay (500);
  }

  delay(1);        // delay in between reads for stability
}
