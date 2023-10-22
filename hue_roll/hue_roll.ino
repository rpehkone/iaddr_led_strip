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
	static uint8_t hue = 0;

	leds[0] = CHSV(hue, 255, 255);
	for (int i = 1; i < NUM_LEDS; i++)
	{
		leds[i] = CHSV(hue + i * (128 / NUM_LEDS), 255, 255);
	}

	FastLED.show();
	hue++;
}
