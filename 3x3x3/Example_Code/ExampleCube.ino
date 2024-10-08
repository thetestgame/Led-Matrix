#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
#define CUBE_SIZE 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel((CUBE_SIZE*CUBE_SIZE*CUBE_SIZE), PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  rainbow(20);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

