void servoProcess() {

  servoShutdown = false;

  Serial.println("liquid process starts");

  servoFindhome();
  servoLiquidDispensing();
  servoFindhome();

  Serial.println("liquid process done");
  Serial.println();
  delay(500);

}
