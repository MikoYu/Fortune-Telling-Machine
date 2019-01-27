#include <Adafruit_NeoPixel.h>

const int NUM_PIXELS = 60;
const int NUM_STRIPS = 6;

// An array of the pin numbers for the strips
const int Pins[NUM_STRIPS] = {2, 3, 4, 5, 6, 7};


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel Strips[NUM_STRIPS] = {
  Adafruit_NeoPixel(NUM_PIXELS, Pins[0], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[4], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXELS, Pins[5], NEO_GRB + NEO_KHZ800)
};

const uint32_t Blue = Adafruit_NeoPixel::Color(10, 10, 255);
const uint32_t Pink = Adafruit_NeoPixel::Color(255, 0, 100);


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    Strips[strip].begin();
  }
  setAllStrips(Blue);
}

void loop() {
  delay(30000UL);
  crossFade(Blue, Pink, 10UL);
  delay(30000UL);
  crossFade(Pink, Blue, 10UL);
}

void setAllStrips(const uint32_t color) {
  byte red = (color >> 16) & 0xff;
  byte green = (color >> 8) & 0xff;
  byte blue = color & 0xff;
  setAllStrips(red, green, blue);
}

void setAllStrips(byte red, byte green, byte blue) {
  // for each strip
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    // for each pixel
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
      Strips[strip].setPixelColor(pixel, red, green, blue);
    }
    Strips[strip].show(); // Output to strip
  }
}

void crossFade(const uint32_t startColor, const uint32_t endColor, unsigned long speed) {
  byte startRed = (startColor >> 16) & 0xff;
  byte startGreen = (startColor >> 8) & 0xff;
  byte startBlue = startColor & 0xff;

  byte endRed = (endColor >> 16) & 0xff;
  byte endGreen = (endColor >> 8) & 0xff;
  byte endBlue = endColor & 0xff;

  // for each step in the cross-fade
  for (int step = 0; step < 256; step++) {
    byte red = map(step, 0, 255, startRed, endRed);
    byte green = map(step, 0, 255, startGreen, endGreen);
    byte blue = map(step, 0, 255, startBlue, endBlue);
    setAllStrips(red, green, blue);
    delay(speed);
  }
}
