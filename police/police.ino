#include <FastLED.h>

#define NUM_LEDS 229
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup()
{
	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
	for (int i = 0; i < 10; i++)
	{
		fill_solid(leds, NUM_LEDS / 2, CRGB::Blue);
		fill_solid(&leds[NUM_LEDS / 2], NUM_LEDS - NUM_LEDS / 2, CRGB::Red);
		FastLED.show();
		delay(80);

		fill_solid(leds, NUM_LEDS / 2, CRGB::Red);
		fill_solid(&leds[NUM_LEDS / 2], NUM_LEDS - NUM_LEDS / 2, CRGB::Blue);
		FastLED.show();
		delay(80);
	}
	for (int i = 0; i < 5; i++)
	{
		fill_solid(leds, NUM_LEDS, CRGB::Red);
		FastLED.show();
		delay(400);
		fill_solid(leds, NUM_LEDS, CRGB::Blue);
		FastLED.show();
		delay(400);
	}
}
