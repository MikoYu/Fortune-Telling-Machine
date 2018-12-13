int solenoidPin = 10; //solenid valve pin; don't have to be PWM
int pushButton = 2;

// 7213 - 2037 = 5176
// 5797 - 646 = 5151
// 6691 - 1383 = 5308
// 7347 - 2055 = 5292
// 6030 - 646 = 5384

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
    delay (5500);

  } else {

    // ramp down the motor speed
    digitalWrite(solenoidPin, LOW); // switch the valve OFF
    Serial.println("valve OFF");
    //delay (500);
  }

  delay(1);        // delay in between reads for stability
}
