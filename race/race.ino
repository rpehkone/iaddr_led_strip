#include <FastLED.h>

#define NUM_LEDS 229
#define LED_PIN 7

CRGB leds[NUM_LEDS];

struct racer
{
	int position;
	int hue;
	int speed;
};

#define NUM_DROPS 5
racer racers[NUM_DROPS];

void setup()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	for (int i = 0; i < NUM_DROPS; ++i)
	{
		racers[i].position = random(0, NUM_LEDS - 1);
		racers[i].hue = random(0, 255);
		racers[i].speed = random(1, 3);
	}
}

void loop()
{
	FastLED.clear(); // its kinda cool without clear
	for (int i = 0; i < NUM_DROPS; ++i)
	{
		racers[i].position += racers[i].speed;
		if (racers[i].position >= NUM_LEDS - 1)
		{
			racers[i].position = random(-20, 0);
			racers[i].hue = random(0, 255);
		}

		if (racers[i].position >= 0 && racers[i].position < NUM_LEDS)
		{
			leds[racers[i].position] = CHSV(racers[i].hue, 255, 255);
		}
	}

	FastLED.show();
	delay(25);
}
