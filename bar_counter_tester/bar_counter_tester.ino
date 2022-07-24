#include <FastLED.h>

static const uint8_t led_pin = 2;
const unsigned long max_leds = 150;
int counts = 0;
CRGB leds[max_leds];

void setup() {
  FastLED.addLeds<WS2812, led_pin, GRB>(leds, max_leds).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(127);
  Serial.begin(19200);
}

void loop() {
  if (Serial.available() > 0) {
    String count = Serial.readStringUntil('\n');
    counts = count.toInt();
    Serial.print("Get numbers: ");
    Serial.println(counts);
    FastLED.clear();
    FastLED.show();
  }

  if (counts == 0) {
    FastLED.clear();
    FastLED.show();
    return;
  } else {
    for (int i = 0; i < counts; i++) {
      leds[i].setRGB(0, 255, 0);
    }
    FastLED.show();
  }

}
