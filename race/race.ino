#include <FastLED.h>

#define NUM_LEDS 229
#define DATA_PIN 7
#define NUM_DROPS 5
#define BRIGHTNESS 64

CRGB leds[NUM_LEDS];

struct Drop
{
	int position;
	int hue;
	int speed;
};

Drop drops[NUM_DROPS];

void setup()
{
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
	for (int i = 0; i < NUM_DROPS; ++i)
	{
		drops[i].position = random(0, NUM_LEDS - 1);
		drops[i].hue = random(0, 255);
		drops[i].speed = random(1, 3);
	}
}

void loop()
{
	FastLED.clear(); // its kinda cool without clear
	for (int i = 0; i < NUM_DROPS; ++i)
	{
		drops[i].position += drops[i].speed;
		if (drops[i].position >= NUM_LEDS - 1)
		{
			drops[i].position = random(-20, 0);
			drops[i].hue = random(0, 255);
		}

		if (drops[i].position >= 0 && drops[i].position < NUM_LEDS)
		{
			leds[drops[i].position] = CHSV(drops[i].hue, 255, 255);
		}
	}

	FastLED.show();
	delay(25);
}
