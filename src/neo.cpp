#include <FastLED.h>
#include "badge.h"
#include "neo.h"

/*
	neo.cpp -- part of the VegasBadge2018 project.
	Implementation of LED functions
*/

/* *** NEO *** */
namespace NEO {

	const uint16_t DATA_PIN = 6;
	const uint16_t NUM_LEDS = 6;
	CRGB leds[NUM_LEDS];
	uint8_t gHue = 0;
	uint8_t patternPosition = 0;
	unsigned long previousPatternMillis = 0;


	// Colors must be incrementing unique values
	// COLORS_NR_ITEMS is always the last value in the list
	const uint8_t NO_COLOR = 0;
	const uint8_t PINK = 1;
	const uint8_t RED = 2;
	const uint8_t GREEN = 3;
	const uint8_t BLUE = 4;
	const uint8_t COLORS_NR_ITEMS = 5;

	uint8_t curColor = 0;

	// Patterns must be incrementing unique values
	// PATTERNS_NR_ITEMS is always the last value in the list
	const uint8_t NO_PATTERN = 0;
	const uint8_t CHASE = 1;
	const uint8_t CONFETTI = 2;
	const uint8_t POPO = 3;
	const uint8_t RAINBOW = 4;
	const uint8_t STROBE = 5;
	const uint8_t SURGE = 6;
	const uint8_t PATTERNS_NR_ITEMS = 7;

	uint8_t curPattern = 0;

	enum modes {
		COLORS,
		PATTERNS,
	};
	enum modes curMode;

	void SetupNeo() {
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	}

	void fadeAll(uint8_t value) {
		for( uint16_t j = 0; j < NUM_LEDS; j++) {
			leds[j].nscale8(value);
		}
	}

	uint8_t checkTime ( uint16_t duration ) {
		uint32_t curMillis = millis();
		if( curMillis - previousPatternMillis >= duration) {
			previousPatternMillis = curMillis;
			return true;
		} else {
			return false;
		}
	}

	void pinkColor() {
		curColor = PINK;
		curPattern = NO_PATTERN;
		setColorMode();
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB(0xff, 0x14, 0x93);
		}
		FastLED.show();
	}

	void redColor() {
		curColor = RED;
		curPattern = NO_PATTERN;
		setColorMode();
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Red;
		}
		FastLED.show();
	}

	void greenColor() {
		curColor = GREEN;
		curPattern = NO_PATTERN;
		setColorMode();
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Green;
		}
		FastLED.show();
	}

	void blueColor() {
		curColor = BLUE;
		curPattern = NO_PATTERN;
		setColorMode();
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}

	/* *** Pattern: Chase *** */
	void chasePattern() {
		curColor = NO_COLOR;
		curPattern = CHASE;
		setPatternMode();
		patternPosition = 0;
	}

	void chasePatternUpdate() {
		if (checkTime(100)) {
			leds[patternPosition] = CHSV(gHue++, 255, 255);
			FastLED.show();
			fadeAll(80);
			if (patternPosition + 1 < NUM_LEDS) {
				patternPosition++;
			} else {
				patternPosition = 0;
			}
		}
	}

	/* *** Pattern: Confetti *** */
	void confettiPattern() {
		curColor = NO_COLOR;
		curPattern = CONFETTI;
		setPatternMode();
		patternPosition = 0;
	}

	void confettiPatternUpdate() {
		if (checkTime(50)) {
			uint16_t pos = random16(NUM_LEDS);
			leds[pos] = CHSV(gHue + random8(64), 200, 255);
			FastLED.show();
			fadeAll(80);
		}
	}

	/* *** Pattern: Popo *** */
	void popoPattern() {
		curColor = NO_COLOR;
		curPattern = POPO;
		setPatternMode();
		patternPosition = 0;
	}

	void popoPatternUpdate() {
		if (checkTime(20)) {
			if (patternPosition == 0 || patternPosition == 3) { 
				leds[0] = CRGB::Red;
				leds[5] = CRGB::Red;
				leds[1] = CRGB::Blue;
				leds[4] = CRGB::Blue;
			} else if (patternPosition == 10 || patternPosition == 13) {
				leds[1] = CRGB::Red;
				leds[4] = CRGB::Red;
				leds[2] = CRGB::Blue;
				leds[3] = CRGB::Blue;
			}
			FastLED.show();
			fadeAll(180);
			if (patternPosition < 20) {
				patternPosition++;
			} else {
				patternPosition = 0;
			}
		}
	}

	/* *** Pattern: Rainbow *** */
	void rainbowPattern() {
		curColor = NO_COLOR;
		curPattern = RAINBOW;
		setPatternMode();
		patternPosition = 0;
	}

	void rainbowPatternUpdate() {
		if (checkTime(50)) {
			fill_rainbow( leds, NUM_LEDS, gHue++, 7);
			FastLED.show();
		}
	}

	/* *** Pattern: Strobe *** */
	void strobePattern() {
		curColor = NO_COLOR;
		curPattern = STROBE;
		setPatternMode();
		patternPosition = 0;
	}

	void strobePatternUpdate() {
		if (checkTime(50)) {
			if (patternPosition < 20 && patternPosition % 2 == 0) { 
				for( uint16_t i = 0; i<NUM_LEDS; i++){
					leds[i] = CRGB(0xff, 0xff, 0xff);
				}
			}
			FastLED.show();
			fadeAll(90);
			if (patternPosition + 1 < 50) {
				patternPosition++;
			} else {
				patternPosition = 0;
			}
		}
	}

	/* *** Pattern: Surge *** */
	void surgePattern() {
		curColor = NO_COLOR;
		curPattern = SURGE;
		setPatternMode();
		patternPosition = 0;

		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}

	void surgePatternUpdate() {
		if (checkTime(100)) {
			for( uint16_t j = 0; j < NUM_LEDS; j++) {
				if (patternPosition < 10) { 
					leds[j].nscale8(200);
				} else {
					leds[j] += leds[j].scale8(250);
				}
			}
			FastLED.show();
			if (patternPosition  < 20) {
				patternPosition++;
			} else {
				patternPosition = 0;
			}
		}
	}

	/* *** Update function *** */
	void UpdateNeo() {
		switch (curPattern) {
			case NO_PATTERN:
				// Nothing to do
				break;
			case CHASE:
				chasePatternUpdate();
				break;
			case CONFETTI:
				confettiPatternUpdate();
				break;
			case POPO:
				popoPatternUpdate();
				break;
			case RAINBOW:
				rainbowPatternUpdate();
				break;
			case STROBE:
				strobePatternUpdate();
				break;
			case SURGE:
				surgePatternUpdate();
				break;
		}
	}

	void cycleColor() {
		curPattern = NO_PATTERN;
		curColor += 1;
		if ( curColor >= COLORS_NR_ITEMS ) {
			curColor = 1;
		}

		switch (curColor) {
			case PINK:
				pinkColor();
				break;
			case RED:
				redColor();
				break;
			case GREEN:
				greenColor();
				break;
			case BLUE:
				blueColor();
				break;
		}
	}

	void cyclePattern() {
		curColor = NO_COLOR;
		curPattern += 1;
		if ( curPattern >= PATTERNS_NR_ITEMS ) {
			curPattern = 1;
		}

		switch (curPattern) {
			case CHASE:
				chasePattern();
				break;
			case CONFETTI:
				confettiPattern();
				break;
			case POPO:
				popoPattern();
				break;
			case RAINBOW:
				rainbowPattern();
				break;
			case STROBE:
				strobePattern();
				break;
			case SURGE:
				surgePattern();
				break;
		}
	}

	void setColorMode() {
		curMode = COLORS;
	}

	void setPatternMode() {
		curMode = PATTERNS;
	}

	void switchMode() {
		if ( curMode == COLORS ) {
			setPatternMode();
		} else {
			setColorMode();
		}
	}

	void cycleMode() {
		if ( curMode == COLORS ) {
			cycleColor();
		} else {
			cyclePattern();
		}
	}

}
