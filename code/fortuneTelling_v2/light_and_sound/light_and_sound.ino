#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define NUM_LEDS 60
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON 3
byte selectedEffect = 0; //A byte stores an 8-bit unsigned number, from 0 to 255.
byte currentEffect;
const int offEffect = 0;

// add time control
unsigned long currentMillis = 0;
unsigned long timerStartMillis = 0;
long interval = 5000;

// for liquid selection
int liqColor1, liqColor2;
// colors for red, orange-ish red, orange, yellow, green, some green, blue, indigo, violet, & white
int reds[] = {0xFF, 0xE2, 0xFF, 0xFF, 0x00, 0x96, 0x00, 0x4B, 0x8B, 0xff};
int greens[] = {0x00, 0x57, 0x7F, 0xFF, 0xFF, 0xbf, 0x00, 0x00, 0x00, 0xff};
int blues[] = {0x00, 0x1E, 0x00, 0x00, 0x00, 0x33, 0xff, 0x82, 0xFF, 0xff};

// for gradient
int startPixel = 0;
int sp = 0;

// for random seed
const int seedPin = A5;

void setup() {
  Serial.begin(9600);
  Serial.println("start");

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  EEPROM.get(0, selectedEffect);
  // EEPROM Get: Get values from EEPROM and prints as float on serial.
  currentEffect = selectedEffect;

  digitalWrite (BUTTON, HIGH);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed

  // use the input on A5 as random seed, to make the selection seem more "random"
  randomSeed(analogRead(seedPin));
}

void loop() {

  if (selectedEffect > 6) {
    selectedEffect = 0;
    currentEffect = 0;
    EEPROM.put(0, 0);
    // if statement has to be at first to make sure selectEffect is from 0 to 6.
  }

  Serial.println(selectedEffect);
  Serial.println(currentEffect);


  switch (currentEffect) {
    case 0:
      // led off
      Serial.println("all off");
      //allOff();   // Black/off
      colorWipe(strip.Color(0, 0, 0), 50);
      break;


    case 1:
      // scan the question (meteorRain)
      Serial.println("scanning");
      meteorRain(0xff, 0xff, 0xff, 10, 64, true, 30);
      /********* ending not ideal, need changes **********/

      // calculating the answer (Sparkle)
      Serial.println("calculating");

      timerStartMillis = millis();
      currentMillis = millis();
      interval = 5000;

      while (currentMillis - timerStartMillis <= interval) {
        Sparkle(0xff, 0xff, 0xff, 50); // white
        currentMillis = millis();
      }

      // calculation done
      Serial.println("calculation done");
      // Strobe - Color (red, green, blue), number of flashes, flash speed, end pause
      Strobe(0xff, 0xff, 0xff, 10, 50, 1000);

      break;

    case 2:
      // choose first liquid
      Serial.println("choose the first liquid");

      // randomly select a color and show it with FadeInOut
      liqColor1 = int(random(0, 10));
      Serial.print("liqColor1: "); Serial.println(liqColor1);
      FadeInOut(reds[liqColor1], greens[liqColor1], blues[liqColor1]); // white
      break;

    case 3:
      // choose second liquid
      Serial.println("choose the second liquid");

      // randomly select a color and show it with FadeInOut
      liqColor2 = int(random(0, 10));
      Serial.print("liqColor2: "); Serial.println(liqColor2);
      FadeInOut(reds[liqColor2], greens[liqColor2], blues[liqColor2]); // white
      break;

    case 4:
      // mixing process
      // tweaked from gradient3
      startPixel = 0;
      sp = 0;

      timerStartMillis = millis();
      currentMillis = millis();
      interval = 5000;

      while (currentMillis - timerStartMillis <= interval) {
        for ( int i = 0; i < NUM_LEDS; i++ ) {
          strip.setPixelColor(sp, 100, i * 2, 255 );

          if ( sp == NUM_LEDS )
            sp = 0;
          else
            sp++;
        }
        strip.show();

        startPixel++;
        if ( startPixel == 60 )
          startPixel = 0;
        currentMillis = millis();

        delay(15);
      }

      strip.clear();
      strip.show();
      break;


    case 5:
      // 1 min countdown
      // colorWipe - Color (red, green, blue), speed delay
      Serial.println("counting down: light up one by one");
      colorWipe(0xff, 0xff, 0xff, 1000); //white
      Serial.println("light off one by one");
      colorWipe(0x00, 0x00, 0x00, 10); //off
      break;

    case 6:
      // present the answer
      Serial.println("present the answer (NewITT-CenterToOutside");
      CenterToOutside(0xff, 0xff, 0xff, 8, 50, 250);
      strip.clear();
      strip.show();
      break;

//    case 7:
//      // anything for test
//      // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
//      Serial.println("Twinkle");
//      Twinkle(0xff, 0x00, 0x00, 10, 100, false);
//
//      break;

  }

  currentEffect = 0;

}

void changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    // no use; but after adding this a bug doesn't show up
    // the bug: if press button when all off, sometimes crush
    //Serial.println("next effect");

    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}


