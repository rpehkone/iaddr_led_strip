#include <EEPROM.h>
#include <FastLED.h>

#define NUM_LEDS 229
#define LED_PIN 7
#define PROGRAM_COUNT 8
#define STATE_ADDR 0 // EEPROM address to store selected program
CRGB leds[NUM_LEDS];

struct racer
{
	int position;
	int hue;
	int speed;
};

#define NUM_DROPS 5
racer racers[NUM_DROPS];
void setup_racers()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	for (int i = 0; i < NUM_DROPS; ++i)
	{
		racers[i].position = random(0, NUM_LEDS - 1);
		racers[i].hue = random(0, 255);
		racers[i].speed = random(1, 3);
	}
}

int currentState = 0;
void setup()
{
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
	currentState = EEPROM.read(STATE_ADDR);
	currentState = (currentState + 1) % PROGRAM_COUNT;
	EEPROM.write(STATE_ADDR, currentState);
	if (currentState == 5) {
		setup_racers();
	}
}

void loop()
{
	switch (currentState)
	{
	case 0:
		christmas();
		break;
	case 1:
		electricity();
		break;
	case 2:
		fire();
		break;
	case 3:
		hue_roll();
		break;
	case 4:
		police();
		break;
	case 5:
		race();
		break;
	case 6:
		roulette();
		break;
	case 7:
		underglow();
		break;
	}
}

bool toggleState = true;
void christmas()
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


int blank_pos = 0.0;
void electricity()
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

void fire()
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

void hue_roll()
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

void police()
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

void race()
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

int whiteIndex = 0;
int spin = NUM_LEDS - 1;
void roulette()
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


void underglow()
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
