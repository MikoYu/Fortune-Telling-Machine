void stepperProcess() {

  Serial.println("pattern part starts");

  stepperFindhome();
  stepperPattern();
  stepperFindhome();

  Serial.println("pattern part done");

}

