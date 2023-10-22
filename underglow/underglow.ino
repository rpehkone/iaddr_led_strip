#include <FastLED.h>

#define NUM_LEDS 229
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup()
{
	FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop()
{
	rainbowCycle(20);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
	FastLED.show();
	colorWipe(CRGB::Blue, 5);
	theaterChase(CRGB::White, 50, 20);
}

void rainbowCycle(uint8_t wait)
{
	uint16_t i, j;
	for (j = 0; j < 256; j++)
	{
		for (i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = solve_hue(((i * 256 / NUM_LEDS) + j) & 255);
		}
		FastLED.show();
		delay(wait);
	}
}

CRGB solve_hue(byte WheelPos)
{
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85)
	{
		return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170)
	{
		WheelPos -= 85;
		return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void colorWipe(CRGB color, uint8_t wait)
{
	for (uint16_t i = 0; i < NUM_LEDS; i++)
	{
		leds[i] = color;
		FastLED.show();
		delay(wait);
	}
}

void theaterChase(CRGB color, uint8_t wait, uint8_t amount)
{
	for (int j = 0; j < amount; j++)
	{
		for (int q = 0; q < 3; q++)
		{
			for (uint16_t i = 0; i + q < NUM_LEDS; i = i + 3)
			{
				leds[i + q] = color;
			}
			FastLED.show();
			delay(wait);

			for (uint16_t i = 0; i + q < NUM_LEDS; i = i + 3)
			{
				leds[i + q] = CRGB::Black;
			}
		}
	}
}

