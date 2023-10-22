#include <FastLED.h>

#define NUM_LEDS 229
#define LED_PIN 7

CRGB leds[NUM_LEDS];
int blank_pos = 0.0;

void setup()
{
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop()
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		if (i < blank_pos + 5 && i > blank_pos - 5) {
			leds[i] = CRGB(0, 0, 0);
		}
		else
		{
			if (random(0, 2))
			{
				leds[i] = CRGB::White;
			}
			else
			{
				leds[i] = CRGB::Blue;
			}

			leds[i].fadeToBlackBy(random(64, 224));
		}
	}

	blank_pos += 2;
	if (blank_pos >= NUM_LEDS)
	{
		blank_pos = 0;
	}

	FastLED.show();
}
