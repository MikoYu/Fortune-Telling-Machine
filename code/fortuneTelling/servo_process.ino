void servoProcess() {

  Serial.println("liquid process starts");
  
  servoFindhome();
  servoLiquidDispensing();
  servoFindhome();

  Serial.println("liquid process done");
  
}
