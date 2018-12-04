// Source: https://www.tweaking4all.com/hardware/arduino/arduino-all-ledstrip-effects-in-one/

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define NUM_LEDS 60
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON 2
byte selectedEffect = 0; //A byte stores an 8-bit unsigned number, from 0 to 255.

void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  digitalWrite (BUTTON, HIGH);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed
  //The first parameter to attachInterrupt() is an interrupt number. Normally you should use digitalPinToInterrupt(pin) to translate the actual digital pin to the specific interrupt number.
  // Arduino Uno digital pins usable for interupts are 2 and 3;
  //Note: Inside the attached function, delay() won’t work and the value returned by millis() will not increment. Serial data received while in the function may be lost. You should declare as volatile any variables that you modify within the attached function. See the section on ISRs below for more information.
  //CHANGE to trigger the interrupt whenever the pin changes value
  // changeEffect: if BUTTON is high, selectedEffect+1, put value in EEPROM (0, selectedEffect)
  // asm volatile ("  jmp 0");

  // maybe everytime when the BUTTON is low, attachInterrupt will be triggered.
}

// *** REPLACE FROM HERE ***
void loop() {
  EEPROM.get(0, selectedEffect);
  // EEPROM Get: Get values from EEPROM and prints as float on serial.

  if (selectedEffect > 18) {
    selectedEffect = 0;
    EEPROM.put(0, 0);
    // if statement has to be at first to make sure selectEffect is from 0 tp 18.
  }


  switch (selectedEffect) {

    case 0  : {
        // scan
        Serial.println("meteorRain");
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0xff, 0xff, 0xff, 10, 64, true, 30);
        break;
      }

    case 1  : {
        Serial.println("Sparkle");
        // Sparkle - Color (red, green, blue), speed delay
        Sparkle(0xff, 0xff, 0xff, 50); // white

        break;
      }

    case 2  : {
        Serial.println("Strobe");
        // Strobe - Color (red, green, blue), number of flashes, flash speed, end pause
        Strobe(0xff, 0xff, 0xff, 10, 50, 1000);

        break;
      }

    case 3  : {
        Serial.println("FadeInOut");
        // FadeInOut - Color (red, green. blue)
        //FadeInOut(0xff, 0x00, 0x00); // red
        FadeInOut(0xff, 0xff, 0xff); // white
        // FadeInOut(0x00, 0x00, 0xff); // blue

        break;

      }

    case 4  : {
        // colorWipe - Color (red, green, blue), speed delay
        Serial.println("light up one by one");
        colorWipe(0xff, 0xff, 0xff, 1000); //white
        Serial.println("light off one by one");
        colorWipe(0x00, 0x00, 0x00, 1000); //off
        break;
      }

    case 5  : {
        // NewKITT - Color (red, green, blue), eye size, speed delay, end pause
        Serial.println("NewITT");
        CenterToOutside(0xff, 0xff, 0xff, 8, 50, 250);

        break;
      }

    case 6  : {
        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
         Serial.println("Twinkle");
         Twinkle(0xff, 0x00, 0x00, 10, 100, false);

        break;
      }

    case 7  : {
        // TwinkleRandom - twinkle count, speed delay, only one (true/false)
        Serial.println("TwinkleRandom");
        TwinkleRandom(20, 100, false);

        break;
      }

    case 8  : {
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
      }

    case 9  : {
        // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
        SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000));
        break;
      }

    case 10 : {
        // Running Lights - Color (red, green, blue), wave dealy
        RunningLights(0xff, 0x00, 0x00, 50); // red
        RunningLights(0xff, 0xff, 0xff, 50); // white
        RunningLights(0x00, 0x00, 0xff, 50); // blue
        break;
      }

    case 11 : {
        // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
        CylonBounce(0xff, 0x00, 0x00, 4, 10, 50);
        Serial.println("CylonBounce");
        break;
      }

    case 12 : {
        // rainbowCycle - speed delay
        rainbowCycle(20);
        break;
      }

    case 13 : {
        // theatherChase - Color (red, green, blue), speed delay
        theaterChase(0xff, 0, 0, 50);
        break;
      }

    case 14 : {
        // theaterChaseRainbow - Speed delay
        theaterChaseRainbow(50);
        break;
      }

    case 15 : {
        // Fire - Cooling rate, Sparking rate, speed delay
        Fire(55, 120, 15);
        break;
      }


    // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
    // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
    // CAUTION: If set to continuous then this effect will never stop!!!

    case 16 : {
        // mimic BouncingBalls
        byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
        BouncingColoredBalls(1, onecolor, false);
        break;
      }

    case 17 : {
        // multiple colored balls
        byte colors[3][3] = { {0xff, 0x00, 0x00},
          {0xff, 0xff, 0xff},
          {0x00, 0x00, 0xff}
        };
        BouncingColoredBalls(3, colors, false);
        break;
      }

    case 18 : {
        // RGBLoop - no parameters
        RGBLoop();
        break;
      }
  }
}

void changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}


