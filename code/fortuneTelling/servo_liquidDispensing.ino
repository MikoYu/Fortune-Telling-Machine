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
  delay(liquidDispensingTime);  // wait for valve; use other funcs later

  // the solenoid valve dispsenses liquid A

  // turn to get liquid B
  Serial.print("to B: \t");
  servoWayfinding(solA, solAforB);
  delay(liquidDispensingTime);  // wait for valve; use other funcs later

  // the other solenoid valve dispsenses liquid B

  // turn counterclockwise to home position and stop
  Serial.print("Back home: \t");
  servoWayfinding(solAforB, homeA);

}


void servoWayfinding(int pos1, int pos2) {
  // calculating clockwise and counterclockwise spinning distance with position before (pos1) and after (pos2) the spinning
  int distCw = (pos2 - pos1 + 8) % 8;
  // int distCcw = (pos1 - pos2 + 8) % 8;
  int turnDegree;
  int servoSpeed;

  Serial.print("distCw: "); Serial.print(distCw); Serial.print("\t");

  switch (distCw) {
    // when pos1 = pos2, turn a little bit and turn back to notify
    case 0:
      Serial.println("case: still");
      turnDegree = 3;
      servoSpeed = 0;
      servoRotating(turnDegree, servoSpeed, 5000);
      turnDegree = 3;
      servoSpeed = 180;
      servoRotating(turnDegree, servoSpeed, 5000);
      break;

    // in the following cases, turn clockwise to get liquid, in max. 10s
    case 1:
    case 2:
    case 3:
    case 4:
      Serial.print("case: cw\t");
      turnDegree = distCw * 5;
      servoSpeed = 0;
      servoRotating(turnDegree, servoSpeed, 10000);
      break;

    // in the following cases, turn counterclockwise to get liquid, in max. 10s
    case 5:
    case 6:
    case 7:
      Serial.print("case: ccw\t");
      turnDegree = (8 - distCw) * 5;
      servoSpeed = 180;
      servoRotating(turnDegree, servoSpeed, 10000);
      break;

  }

  Serial.print("turnDegree: "); Serial.print(turnDegree); Serial.print("\t");
  Serial.print("servoSpeed: "); Serial.print(servoSpeed); Serial.println("\t");

}


void servoRotating(int degree, int angleSpeed, int maxTime) {
  // maxTime should >= 50;
  for (int servoTimer = 0; servoTimer < maxTime; servoTimer += 50) {
    rotaryEncoder();
    if (abs(rtCounter) < degree) {
      myservo.write(angleSpeed);
    } else {
      myservo.writeMicroseconds(stopSpeed);
      rtCounter = 0;
      break;
    }

    // for forced shutdown
    if (digitalRead(servoBtnPin) == HIGH) {
      myservo.writeMicroseconds(stopSpeed);
      break;
    }


  }
}




