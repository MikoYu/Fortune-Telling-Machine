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

// colors for red, orange-ish red, orange, yellow, geen, ...
int reds[] = {0xFF, 0xE2, 0xFF, 0xFF, 0x00, 0x96, 0x00, 0x4B, 0x8B, 0xff};
int greens[] = {0x00, 0x57, 0x7F, 0xFF, 0xFF, 0xbf, 0x00, 0x00, 0x00, 0xff};
int blues[] = {0x00, 0x1E, 0x00, 0x00, 0x00, 0x33, 0xff, 0x82, 0xFF, 0xff};
//Some Green (Hex: #) (RGB: 150, 191, 51)
//Blue (Hex: #00FF) (RGB: 0, 0, 255)
//Indigo (Hex: #00) (RGB: 75, 0, 130)
//Violet  (Hex: #) (RGB: 139, 0, 255)
//White   (Hex: #ffff) (RGB: 255, 255, 255)

int liqColor1, liqColor2;
int startPixel = 0;
int sp = 0;
//int brightness = 0;

// for random seed
const int seedPin = A5;

void setup()
{
  Serial.begin(9600);
  Serial.println("start");

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  EEPROM.get(0, selectedEffect);
  // EEPROM Get: Get values from EEPROM and prints as float on serial.
  currentEffect = selectedEffect;

  digitalWrite (BUTTON, HIGH);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // change effect once the button is pressed

  // use the input on A5 as random seed, to make the selection seem more "random"
  randomSeed(analogRead(seedPin));

  /*
    The first parameter to attachInterrupt() is an interrupt number.
    Normally you should use digitalPinToInterrupt(pin) to translate the actual digital pin to the specific interrupt number.
    Arduino Uno digital pins usable for interupts are 2 and 3;
    Note: Inside the attached function, delay() won’t work and the value returned by millis() will not increment.
    Serial data received while in the function may be lost.
    You should declare as volatile any variables that you modify within the attached function. See the section on ISRs below for more information.
  */
  /*
    //CHANGE to trigger the interrupt whenever the pin changes value
    // changeEffect: if BUTTON is high, selectedEffect+1, put value in EEPROM (0, selectedEffect)
    // asm volatile ("  jmp 0");
  */

}


void loop() {


  if (selectedEffect > 7) {   // all = 19
    selectedEffect = 0;
    currentEffect = 0;
    EEPROM.put(0, 0);
    // if statement has to be at first to make sure selectEffect is from 0 tp 18.
  }

  Serial.println(selectedEffect);
  Serial.println(currentEffect);

  switch (currentEffect) {
    case 0:
      // led off
      Serial.println("led off");
      allOff();   // Black/off
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
      //
      //      for ( int i = 0; i < 30; i++ ) {
      //        strip.setPixelColor(i, reds[liqColor1], greens[liqColor1], blues[liqColor1]);
      //      }
      //      for ( int i = 30; i < 60; i++ ) {
      //        strip.setPixelColor(i, reds[liqColor2], greens[liqColor2], blues[liqColor2]);
      //      }
      //
      //      delay(100);


    // tweaked from gradient3
//      startPixel = 0;
//      sp = 0;
//
//      timerStartMillis = millis();
//      interval = 5000;
//
//      while (currentMillis - timerStartMillis <= interval) {
//        for ( int i = 0; i < NUM_LEDS; i++ ) {
//          strip.setPixelColor(sp, 100, i * 2, 255 );
//
//          if ( sp == NUM_LEDS )
//            sp = 0;
//          else
//            sp++;
//        }
//        strip.show();
//
//        startPixel++;
//        if ( startPixel == 60 )
//          startPixel = 0;
//        currentMillis = millis();
//      }
//
//      allOff();
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
      /********* ending not ideal, need changes **********/
      break;

    case 7:
      // test only


      // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
      Serial.println("Twinkle");
      Twinkle(0xff, 0x00, 0x00, 10, 100, false);

      break;

      /*

        case 8  :
          // TwinkleRandom - twinkle count, speed delay, only one (true/false)
          Serial.println("TwinkleRandom");
          TwinkleRandom(20, 100, false);

          break;


        case 9  :
          // HalloweenEyes - Color (red, green, blue), Size of eye, space between eyes, fade (true/false), steps, fade delay, end pause
          HalloweenEyes(0xff, 0x00, 0x00,
                        1, 4,
                        true, random(5, 50), random(50, 150),
                        random(1000, 10000));
          HalloweenEyes(0xff, 0x00, 0x00,
                        1, 4,
                        true, random(5, 50), random(50, 150),
                        random(1000, 10000));
          break;


        case 10  :
          // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
          SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000));
          break;

        case 11 :
          // Running Lights - Color (red, green, blue), wave dealy
          RunningLights(0xff, 0x00, 0x00, 50); // red
          RunningLights(0xff, 0xff, 0xff, 50); // white
          RunningLights(0x00, 0x00, 0xff, 50); // blue
          break;


        case 12 :
          // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
          CylonBounce(0xff, 0x00, 0x00, 4, 10, 50);
          Serial.println("CylonBounce");
          break;


        case 13 :
          // rainbowCycle - speed delay
          rainbowCycle(20);
          break;

        case 14 :
          // theatherChase - Color (red, green, blue), speed delay
          theaterChase(0xff, 0, 0, 50);
          break;


        case 15 :
          // theaterChaseRainbow - Speed delay
          theaterChaseRainbow(50);
          break;


        case 16 :
          // Fire - Cooling rate, Sparking rate, speed delay
          Fire(55, 120, 15);
          break;


        // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
        // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
        // CAUTION: If set to continuous then this effect will never stop!!!

        case 17 :
          // mimic BouncingBalls
          byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
          BouncingColoredBalls(1, onecolor, false);
          break;

        case 18 :
          // multiple colored balls
          byte colors[3][3] = { {0xff, 0x00, 0x00},
            {0xff, 0xff, 0xff},
            {0x00, 0x00, 0xff}
          };
          BouncingColoredBalls(3, colors, false);
          break;

        case 19 :
          // RGBLoop - no parameters
          RGBLoop();
          break;

      */

  }

  currentEffect = 0;

}

void changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}


