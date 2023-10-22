#include <FastLED.h>

#define NUM_LEDS 229
#define LED_PIN 7

CRGB leds[NUM_LEDS];

int whiteIndex = 0;
int spin;

void setup()
{
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
	spin = NUM_LEDS - 1;
}

void loop()
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		int k = i - spin;
		if (k < 0) {
			k += NUM_LEDS;
		}
		if (k >= 108 && k <= 113)
		{
			leds[i] = CRGB(0, 255, 0);
		}
		else if ((k % 6) < 3)
		{
			leds[i] = CRGB(128, 0, 0);
		}
		else
		{
			leds[i] = CRGB(0, 1, 2);
		}
	}

	leds[whiteIndex] = CRGB(255, 255, 255);
	FastLED.show();
	whiteIndex = (whiteIndex + 1) % NUM_LEDS;
	spin--;
	if (spin < 0) {
		spin = NUM_LEDS - 1;
	}
	delay(20);
}
