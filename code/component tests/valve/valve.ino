int solenoidPin = 4; //solenid valve pin

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(solenoidPin, HIGH); // switch the valve ON
  Serial.println("valve ON");
  delay (10000);
  
  digitalWrite(solenoidPin, LOW); // switch the valve OFF
  Serial.println("valve OFF");
  delay (10000);
  
}
