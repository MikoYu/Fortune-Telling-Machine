//////////// GENERAL ////////////
int machineCaseNo = 4;

//////////// VALVES ////////////
// set up constant pins
const int valvePins[] = {8, 9, 10, 11, 12, 13};

// set up variables for the working valve
int workingValve = 1;
int workingPin = 8;

// for random seed
const int seedPin = A5;

//////////// FOR NEOPIXEL ////////////
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define NUM_LEDS 90
#define LED_PIN 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON 2
byte selectedEffect = 0; //A byte stores an 8-bit unsigned number, from 0 to 255.
byte currentEffect;
const int offEffect = 0;

// add time control
unsigned long currentMillis = 0;
unsigned long timerStartMillis = 0;
long interval = 5000;

// for liquid selection
//int liqColor1, liqColor2;
//int liqColor[] = {0, 0};
// colors for red, orange-ish red, orange, yellow, green, some green, blue, indigo, violet, & white
//int reds[] = {0xFF, 0xE2, 0xFF, 0xFF, 0x00, 0x96, 0x00, 0x4B, 0x8B, 0xff};
//int greens[] = {0x00, 0x57, 0x7F, 0xFF, 0xFF, 0xbf, 0x00, 0x00, 0x00, 0xff};
//int blues[] = {0x00, 0x1E, 0x00, 0x00, 0x00, 0x33, 0xff, 0x82, 0xFF, 0xff};

// for gradient
int startPixel = 0;
int sp = 0;


// /*
//////////// FOR DPMiniPlayer ////////////
#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

// pin that tells whether any music is playing
const int busyPin = 7;

// implement a notification class, its member methods will get called
class Mp3Notify {
  public:
    static void OnError(uint16_t errorCode) {
      // see DfMp3_Error for code meaning
      Serial.println();
      Serial.print("Com Error ");
      Serial.println(errorCode);
    }

    static void OnPlayFinished(uint16_t globalTrack) {
      Serial.println();
      Serial.print("Play finished for #");
      Serial.println(globalTrack);
    }

    static void OnCardOnline(uint16_t code) {
      Serial.println();
      Serial.print("Card online ");
      Serial.println(code);
    }

    static void OnCardInserted(uint16_t code) {
      Serial.println();
      Serial.print("Card inserted ");
      Serial.println(code);
    }

    static void OnCardRemoved(uint16_t code) {
      Serial.println();
      Serial.print("Card removed ");
      Serial.println(code);
    }
};

// instance a DFMiniMp3 object
SoftwareSerial secondarySerial(6, 5); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

// */

void setup() {
  Serial.begin(9600);
  Serial.println("initializing...");

  // set up pin modes
  pinMode(BUTTON, INPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(valvePins[i], OUTPUT);
  }
  pinMode(workingPin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(seedPin, INPUT);
  pinMode(busyPin, INPUT);

  digitalWrite (BUTTON, HIGH);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed

  // use the input on A5 as random seed, to make the selection seem more "random"
  randomSeed(analogRead(seedPin));

  //////////// valves ////////////
  for (int i = 0; i < 6; i++) {
    digitalWrite(valvePins[i], LOW); // switch all the valves OFF
  }

  //////////// NEOPIXEL ////////////
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  EEPROM.get(0, selectedEffect);
  // EEPROM Get: Get values from EEPROM and prints as float on serial.
  currentEffect = selectedEffect;

  //////////// DPMiniPlayer ////////////
  mp3.begin();

  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(30);

  uint16_t count = mp3.getTotalTrackCount();
  Serial.print("files ");
  Serial.println(count);

  //////////// everything's ready ////////////
  Serial.println("starting...");
}

void loop() {

  if (selectedEffect > machineCaseNo) {
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
      Serial.println("start working");
      machineScan();
      break;

    case 2:
      // choose first liquid
      Serial.println("choose the first liquid");
      machineLiquid(1);
      break;

    case 3:
      // choose second liquid
      Serial.println("choose the second liquid");
      machineLiquid(2);
      break;

    case 4:
      // mixing process
      Serial.println("making process");
      //mp3.playMp3FolderTrack(3);
      machineMaking();

      break;

      //    case 5: // test only
      //      Serial.println("testing effects");
      //
      //      machineTest();


  }

  currentEffect = 0;

}

void changeEffect() {
  if (digitalRead (BUTTON) == HIGH) {
    // no use; but after adding this a bug doesn't show up
    // the bug: if press button when all off, sometimes crush
    //Serial.println("next effect");

    selectedEffect++;
    mp3.stop();
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}


