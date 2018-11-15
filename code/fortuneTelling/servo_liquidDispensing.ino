void servoLiquidDispensing() {

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

  turnDegreeA = abs(distanceA) * 5;
  turnDegreeB = abs(distanceB) * 5;
  turnDegreeBack = abs(distanceBack) * 5;

  // turn to get liquid A
  if (solA == 0) {
    // Keep still for 5 sec
    myservo.writeMicroseconds(stopSpeed);
  }
  else {
    // turn clockwise to get liquid A, in max. 15 sec
    for (int servoTimer = 0; servoTimer < 150000; servoTimer += 50) {
      rotaryEncoder();
      if (abs(rtCounter) < turnDegreeA) {
        myservo.write(0);
      } else {
        myservo.writeMicroseconds(stopSpeed);
        rtCounter = 0;
        break;
      }

      // to shutdown
      //      if (digitalRead(servoBtnPin) == HIGH) {
      //        break;
      //      }
    }
  }
  delay(liquidDispensingTime);  // wait 5 sec for valve; use other funcs later

  // the solenoid valve dispsenses liquid A

  // turn to get liquid B
  if (distanceB == 0) {
    // keep still for 5 sec
    myservo.writeMicroseconds(stopSpeed);
  }
  else if (distanceB > 0) {
    // turn clockwise to get liquid B, in max. 15 sec
    for (int servoTimer = 0; servoTimer < 150000; servoTimer += 50) {
      rotaryEncoder();
      if (abs(rtCounter) < turnDegreeB) {
        myservo.write(0);
      } else {
        myservo.writeMicroseconds(stopSpeed);
        rtCounter = 0;
        break;
      }

      // to shutdown
      //      if (digitalRead(servoBtnPin) == HIGH) {
      //        break;
      //      }

    }
  } else {
    // turn counterclockwise to get liquid B, in max. 15 sec
    for (int servoTimer = 0; servoTimer < 150000; servoTimer += 50) {
      rotaryEncoder();
      if (abs(rtCounter) < turnDegreeB) {
        myservo.write(180);
      } else {
        myservo.writeMicroseconds(stopSpeed);
        rtCounter = 0;
        break;
      }

      // to shutdown
      //      if (digitalRead(servoBtnPin) == HIGH) {
      //        break;
      //      }
    }
  }
  delay(liquidDispensingTime);  // wait 5 sec for valve; use other funcs later

  // the other solenoid valve dispsenses liquid B

  // turn counterclockwise to home position and stop
  for (int servoTimer = 0; servoTimer < 150000; servoTimer += 50) {
    rotaryEncoder();
    if (abs(rtCounter) < turnDegreeBack) {
      myservo.write(180);
    } else {
      myservo.writeMicroseconds(stopSpeed);
      rtCounter = 0;
      break;
    }
  }



}
