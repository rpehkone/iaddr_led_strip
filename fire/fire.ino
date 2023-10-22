#include <FastLED.h>

#define NUM_LEDS 229
#define LED_PIN 7

CRGB leds[NUM_LEDS];

void setup()
{
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop()
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		int flicker = random(32, 128); // Random brightness for flicker
		float progress = i / (float)NUM_LEDS;
		int r = random(100, 120 + (int)(progress * 135)); // More red towards the end
		int g = random(20, 60);							  // Random green value

		leds[i] = CRGB(r, g, 0);
		leds[i].fadeToBlackBy(flicker);
	}
	FastLED.show();
}
