#include <FastLED.h>

#define NUM_LEDS 229
#define LED_PIN 7

CRGB leds[NUM_LEDS];
bool toggleState = true;

void setup()
{
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop()
{
	if (toggleState)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = (i % 2 == 0) ? CRGB::Green : CRGB::Red;
		}
	}
	else
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = (i % 2 == 0) ? CRGB::Red : CRGB::Green;
		}
	}

	toggleState = !toggleState;
	FastLED.show();
	delay(1000);
}
