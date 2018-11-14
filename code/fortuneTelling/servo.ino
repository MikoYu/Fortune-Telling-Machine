
void servoProcess() {
  // read the state of the button and check if it is pressed
  if (digitalRead(servoBtnPin) == HIGH) {
    Serial.println("servo button on");

    // pick the liquid for A and B randomly
    solA = int(random(0, solCounts));
    solB = int(random(0, solCounts));
    Serial.print("A: "); Serial.println(solA);
    Serial.print("B: "); Serial.println(solB);

    // calculate turning direction and time
    distanceA = solA - homeA;
    solAforB = (solB + 4) % 8;
    distanceB = solAforB - solA;
    distanceBack = homeA - solAforB;
    Serial.print("A': "); Serial.println(solAforB);
    Serial.print("distance A: "); Serial.println(distanceA);
    Serial.print("distance B: "); Serial.println(distanceB);
    Serial.print("distance Back: "); Serial.println(distanceBack);

    // rough turning time; cannot use finally
    turnTimeA = TURN_TIME / 8 * abs(distanceA);
    turnTimeB = TURN_TIME / 8 * abs(distanceB);
    turnTimeBack = TURN_TIME / 8 * abs(distanceBack);

    // turn to get liquid A
    if (solA == 0) {
      // Keep still for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }
    else {
      // turn clockwise to get liquid A
      myservo.write(0);
      delay(turnTimeA);
      // stop for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }

    // the solenoid valve dispsenses liquid A

    // turn to get liquid B
    if (distanceB == 0) {
      // leep still for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }
    else if (distanceB > 0) {
      // turn clockwise to get liquid B
      myservo.write(0);
      delay(turnTimeB);
      // stop for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    } else {
      // turn clockwise to get liquid B
      myservo.write(180);
      delay(turnTimeB);
      // stop for 5 sec
      myservo.writeMicroseconds(1415);
      delay(5000);
    }

    // the other solenoid valve dispsenses liquid B

    // turn to home position and stop
    myservo.write(180);
    delay(turnTimeBack);
    // stop for 5 sec
    myservo.writeMicroseconds(1415);
    Serial.println("liquid part done");

  }
  else {
    //Serial.println("pushButton off");
  }

  // delay in between reads for stability
  delay(1);

}
