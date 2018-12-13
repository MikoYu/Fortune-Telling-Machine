void machineScan() {
  // play canning and calculating sound
  Serial.println("play track 1");
  mp3.playMp3FolderTrack(1);  // sd:/mp3/0001.mp3

  // scan the question
  Serial.println("scanning");
  meteorRain(0xff, 0xff, 0xff, 10, 64, true, 20);

  // calculating the answer (Sparkle)
  Serial.println("calculating");
  timerStartMillis = millis();
  currentMillis = millis();
  interval = 5000;

  while (currentMillis - timerStartMillis < interval) {
    Sparkle(0xff, 0xff, 0xff, 50); // white
    currentMillis = millis();
  }

  // calculation done
  Serial.println("calculation done");
  Strobe(0xff, 0xff, 0xff, 10, 50, 8000);
}


void machineLiquid(int liqNo) {
  // play valve sound
  Serial.println("play track 2");
  mp3.playMp3FolderTrack(2);  // sd:/mp3/0002.mp3

  // randomly choose one valve as the working one
  workingValve = int(random(1, 7));
  Serial.print("valve no. "); Serial.print(workingValve); Serial.print(" ON");
  workingPin = valvePins[workingValve - 1];
  Serial.print(" pin no. "); Serial.print(workingPin);
  Serial.println();

  // switch on working pin
  digitalWrite(workingPin, HIGH); // switch the valve ON
  // switch off the valve and stop the music; time controlled by how long the light effect takes 
  FadeInOut(255, 255, 255, 6); // white
  digitalWrite(workingPin, LOW);
  Serial.println("valve OFF");
  mp3.stop();

}

void machineMaking() {
  // bass, frogs, bubbles
  mp3.playMp3FolderTrack(4);  // sd:/mp3/0004.mp3
  Serial.println("play bass (no.4)");
  machineBass();
  while (digitalRead(busyPin) == false) {
    gradient();
  }

  // background noise
  mp3.playMp3FolderTrack(5);  // sd:/mp3/0005.mp3
  Serial.println("play bgd (no.5)");
  strip.setBrightness(24);
  RunningLights(0xff, 0xff, 0xff, 100);
  strip.setBrightness(255);

  // stirring, hoarse sound
  mp3.playMp3FolderTrack(6);  // sd:/mp3/0006.mp3
  Serial.println("play stirring (no.6)");
  theaterChase(0xff, 0xff, 0xff, 50, 65); // stirring for 10 sec
  while (digitalRead(busyPin) == false) {
    SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000));
  }

  // background noise
  mp3.playMp3FolderTrack(7);  // sd:/mp3/0007.mp3
  Serial.println("play bgd (no.7)");
  RunningLights(0x36, 0x36, 0x36, 130);  // a tiny little bit long

  // bubbles
  playTrack(8);
  Serial.println("play bubbles(no.8) with new method");
  while (digitalRead(busyPin) == false) {
    gradient();
  }

  // background noise
  mp3.playMp3FolderTrack(9);  // sd:/mp3/0009.mp3
  Serial.println("play bgd (no.9)");
  strip.setBrightness(24);
  RunningLights(0xff, 0xff, 0xff, 130);

  strip.clear();
  strip.show();
  strip.setBrightness(255);

  // 1 min countdown and present answer
  mp3.playMp3FolderTrack(10);  // sd:/mp3/0010.mp3
  Serial.println("play countdown (no.10)");
  // colorWipe - Color (red, green, blue), speed delay
  Serial.println("counting down: light up one by one");
  colorWipe(0xff, 0xff, 0xff, 600); //white
  Serial.println("light off one by one");
  colorWipe(0x00, 0x00, 0x00, 10); //off
  // present the answer
  Serial.println("present the answer (CenterToOutside");
  CenterToOutside(0xff, 0xff, 0xff, 8, 60, 250);
  strip.clear();
  strip.show();

}

void machineBass() {
  timerStartMillis = millis();
  currentMillis = millis();
  interval = 10000;

  while (currentMillis - timerStartMillis <= interval) {
    HalloweenEyes(0xff, 0xff, 0xff,
                  2, 4,
                  true, 15, 100,
                  3000);
    currentMillis = millis();
  }
}

