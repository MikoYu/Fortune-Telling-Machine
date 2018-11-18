// for random liquid selection
int solA, solB, solAforB;
// count of solutions = 8;

// home position of A and B
int homeA = 0;
int homeB = 4;
// to define current positions of A & B, posB = (posA + 4) % 8

// waiting time when dispensing liquid
const int liquidDispensingTime = 7000;

//////////// functions ////////////
void servoLiquidDispensing() {

  // pick the liquid for A and B randomly
  solA = int(random(0, 8));
  solB = int(random(0, 8));
  solAforB = (solB + 4) % 8;
  Serial.print("A: "); Serial.print(solA);
  Serial.print("\tB: "); Serial.print(solB);
  Serial.print("\tA': "); Serial.println(solAforB);

  // turn to get liquid A
  Serial.print("to A: \t");
  servoWayfinding(homeA, solA);
  Serial.println("arrive at A");

  if (servoShutdown == false) {
    Serial.println("delaying for liquid A dispensing; change later");
    delay(liquidDispensingTime);  // wait for valve; use other funcs later
  }

  // turn to get liquid B
  Serial.print("to B: \t");
  servoWayfinding(solA, solAforB);
  Serial.println("arrive at B");

  if (servoShutdown == false) {
    Serial.println("delaying for liquid B dispensing; change later");
    delay(liquidDispensingTime);  // wait for valve; use other funcs later
  }


  // turn counterclockwise to home position and stop
  Serial.print("Go home: \t");
  servoWayfinding(solAforB, homeA);
  Serial.println("back");

}


void servoWayfinding(int pos1, int pos2) {
  // calculating clockwise and counterclockwise spinning distance with position before (pos1) and after (pos2) the spinning
  int distCw = (pos2 - pos1 + 8) % 8;
  // int distCcw = (pos1 - pos2 + 8) % 8;
  int turnDegree;
  int servoSpeed;

  if (servoShutdown == true) {
    Serial.println("following process terminated");
  }

  else {

    Serial.print("distCw: "); Serial.print(distCw); Serial.print("\t");

    switch (distCw) {
      // when pos1 = pos2, turn a little bit and turn back to notify
      case 0:
        Serial.println("case: still");
        turnDegree = 3;
        servoSpeed = 0;
        servoRotating(turnDegree, servoSpeed);
        turnDegree = 3;
        servoSpeed = 180;
        servoRotating(turnDegree, servoSpeed);
        break;

      // in the following cases, turn clockwise to get liquid, in max. 10s
      case 1:
      case 2:
      case 3:
      case 4:
        Serial.print("case: cw\t");
        turnDegree = distCw * 5;
        servoSpeed = 0;
        servoRotating(turnDegree, servoSpeed);
        break;

      // in the following cases, turn counterclockwise to get liquid, in max. 10s
      case 5:
      case 6:
      case 7:
        Serial.print("case: ccw\t");
        turnDegree = (8 - distCw) * 5;
        servoSpeed = 180;
        servoRotating(turnDegree, servoSpeed);
        break;

    }

  }

}



void servoRotating(int degree, int angleSpeed) {

  if (servoShutdown == true) {
    Serial.println("following process terminated");
  } else {

    Serial.print("turnDegree: "); Serial.print(degree); Serial.print("\t");
    Serial.print("servoSpeed: "); Serial.print(angleSpeed); Serial.println("\t");

    currentMillis = millis();
    servoPreviousMillis = currentMillis;

    for (int i = 0; i < 100000; i += 1) {
      currentMillis = millis();
      deltaMillis = currentMillis - servoPreviousMillis;

      //////////// cases to stop the servo ////////////
      if (deltaMillis >= 10000) {
        Serial.println("rotary encoder error, can't find the liquid");
        servoShutdown = true;
      }

      // can be shutdown immediately during the process
      if (deltaMillis > 500 && digitalRead(servoBtnPin) == HIGH) {
        servoShutdown = true;
        Serial.println("forced shutdown");
      }


      if (servoShutdown == true) {
        myservo.writeMicroseconds(stopSpeed);
        break;
      }

      //////////// rotate to find the liquid ////////////
      rotaryEncoder();
      //Serial.println(rtCounter);
      if (abs(rtCounter) < degree) {
        myservo.write(angleSpeed);
      } else {
        myservo.writeMicroseconds(stopSpeed);
        rtCounter = 0;
        break;
      }

    }
  }
}


