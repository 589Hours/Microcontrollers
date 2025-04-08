#include <FastLED.h>
#include "Wire.h"

#define LED_PIN     14
#define NUM_LEDS    8
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

static const uint8_t addr = 0x55;
static const int sdaPin = 21;
static const int sclPin = 22;
static const uint32_t frequency = 100000;

void onReceive(int len) {
  Serial.printf("onReceive[%d]: ", len);
  while (Wire.available()) { 
    int data = Wire.read();
    Serial.println(data);
    ProcessDistance(data);
  }
}

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Wire.onReceive(onReceive);
    Wire.begin(addr, sdaPin, sclPin, frequency);

    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = NOBLEND;
}


void loop()
{
}

void TestLEDs() {
    ProcessDistance(40); // 8 leds green
    Serial.println("LEDS on green!");
    FastLED.delay(2000 / UPDATES_PER_SECOND);

    ProcessDistance(100); // 4 leds red, 4 leds yellow
    Serial.println("LEDS on yellow and red!");
    FastLED.delay(2000 / UPDATES_PER_SECOND);

    ProcessDistance(80); // 8 leds yellow
    Serial.println("LEDS on yellow!");
    FastLED.delay(2000 / UPDATES_PER_SECOND);

    ProcessDistance(120); // 8 leds red
    Serial.println("LEDS on red!");
    FastLED.delay(2000 / UPDATES_PER_SECOND);

    ProcessDistance(60); // 4 leds yellow, 4 leds green
    Serial.println("LEDS on green and yellow!");
    FastLED.delay(2000 / UPDATES_PER_SECOND);
}

#define GREEN_CASE 2
#define YELLOW_CASE 1
#define RED_CASE 0

int yellowDirection;
int pastColor;

void ProcessDistance(int distance) {
  // 40 cm for 8 LEDS so that means 5 cm for each LED
  if (distance <= 40) {
    // set all to red
    turnLEDsRed(0, NUM_LEDS);
  } else if (distance <= 80) {
    // set to yellow & red
    int yellowLEDs = (distance / 5) % 8;
    turnLEDsRed(0, NUM_LEDS-yellowLEDs);
    if (distance == 80) { // if all 8 leds yellow, return.
      turnLEDsYellow(0, NUM_LEDS);
      return;
    }
    turnLEDsYellow(NUM_LEDS-yellowLEDs, NUM_LEDS);
  } else if (distance < 120) {
    // set to yellow & green
    int yellowLEDs = (distance / 5) % 8;
    turnLEDsGreen(NUM_LEDS-yellowLEDs, NUM_LEDS);
    turnLEDsYellow(0, NUM_LEDS-yellowLEDs);
  } else {
    // set all to green
    turnLEDsGreen(0, NUM_LEDS);
  }


// defines color positions in the rainbow palette
#define GREEN 6
#define YELLOW 3
#define RED 0

void turnLEDsGreen(int start, int end) {
  for (int i = start; i < end; i++) {
    SetLEDColor(i, (uint8_t) GREEN);
  }
}

void turnLEDsYellow(int start, int end) {
  for (int i = start; i < end; i++) {
    SetLEDColor(i, (uint8_t) YELLOW);
  }
}

void turnLEDsRed(int start, int end) {
 for (int i = start; i < end; i++) {
    SetLEDColor(i, (uint8_t) RED);
  }
}

void SetLEDColor(int ledId, uint8_t colorIndex) {
    if (ledId >= NUM_LEDS) {
      Serial.println("Invalid ledId");
      return;
    }

    uint8_t brightness = 255;

    // scale for palette
    colorIndex = colorIndex * 16;

    // set color & show
    leds[ledId] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    FastLED.show();
}



