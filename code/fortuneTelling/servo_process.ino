void servoProcess() {

  Serial.println("liquid part starts");
  
  servoFindhome();
  servoLiquidDispensing();
  servoFindhome();

  Serial.println("liquid part done");
  
}
