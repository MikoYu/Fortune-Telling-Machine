
void pixelStartShow(int i) {
  switch (i) {
    case 0:
      Serial.println("led off");
      colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
      break;
    case 1:
      Serial.println("scanning the question");
      scan();
      colorWipe(strip.Color(0, 0, 0), 0);
      break;
    case 2:
      Serial.println("producing the anwser");
      colorWipe(strip.Color(120, 127, 150), 50);  //all white
      break;
    case 3: 
      Serial.println("ready to offer the answer");
      theaterChase(strip.Color(127, 127, 127), 50); // White, blinking & chasing
      break;

  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


void scan() {
  for (int i = 0; i < 127; i++) {

    strip.setPixelColor(pos - 4, strip.Color(120, 127, 150)); // Dark red
    strip.setPixelColor(pos - 3, strip.Color(120, 150, 150)); // Medium red
    strip.setPixelColor(pos - 2, strip.Color(120, 180, 150)); // Center pixel is brightest
    strip.setPixelColor(pos - 1, strip.Color(120, 200, 150)); // Medium red
    strip.setPixelColor(pos , strip.Color(120, 255, 150)); // Dark red

    strip.show();
    delay(30);

    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for (int j = -4; j <= 0; j++) strip.setPixelColor(pos + j, 0);

    // Bounce off ends of strip
    pos += dir;
    if (pos < 1) {
      pos = 1;
      dir = -dir;
    } else if (pos >= strip.numPixels() + 4) {
      pos = strip.numPixels() + 3;
      dir = -dir;

    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

