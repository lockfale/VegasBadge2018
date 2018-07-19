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
	uint8_t cyclePosition = 0;
	unsigned long previousPatternMillis = 0;

	enum patterns {
		NO_PATTERN,
		CHASE,
		CONFETTI,
		POPO,
		RAINBOW,
		STROBE,
		SURGE,
	};
	enum patterns curPattern;

	void SetupNeo() {
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	}

	void fadeall(uint8_t value) {
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
		curPattern = NO_PATTERN;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB(0xff, 0x14, 0x93);
		}
		FastLED.show();
	}

	void redColor() {
		curPattern = NO_PATTERN;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Red;
		}
		FastLED.show();
	}

	void greenColor() {
		curPattern = NO_PATTERN;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Green;
		}
		FastLED.show();
	}

	void blueColor() {
		curPattern = NO_PATTERN;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}

	/* *** Pattern: Chase *** */
	void chasePattern() {
		curPattern = CHASE;
		cyclePosition = 0;
	}

	void chasePatternUpdate() {
		if (checkTime(100)) {
			leds[cyclePosition] = CHSV(gHue++, 255, 255);
			FastLED.show();
			fadeall(80);
			if (cyclePosition + 1 < NUM_LEDS) {
				cyclePosition++;
			} else {
				cyclePosition = 0;
			}
		}
	}

	/* *** Pattern: Confetti *** */
	void confettiPattern() {
		curPattern = CONFETTI;
		cyclePosition = 0;
	}

	void confettiPatternUpdate() {
		if (checkTime(100)) {
			uint16_t pos = random16(NUM_LEDS);
			leds[pos] = CHSV(gHue + random8(64), 200, 255);
			FastLED.show();
			fadeall(80);
		}
	}

	/* *** Pattern: Popo *** */
	void popoPattern() {
		curPattern = POPO;
		cyclePosition = 0;
	}

	void popoPatternUpdate() {
		if (checkTime(50)) {
			if (cyclePosition == 0 || cyclePosition == 3) { 
				leds[0] = CRGB::Red;
				leds[5] = CRGB::Red;
				leds[1] = CRGB::Blue;
				leds[4] = CRGB::Blue;
			} else if (cyclePosition == 10 || cyclePosition == 13) {
				leds[1] = CRGB::Red;
				leds[4] = CRGB::Red;
				leds[2] = CRGB::Blue;
				leds[3] = CRGB::Blue;
			}
			FastLED.show();
			fadeall(180);
			if (cyclePosition < 20) {
				cyclePosition++;
			} else {
				cyclePosition = 0;
			}
		}
	}

	/* *** Pattern: Rainbow *** */
	void rainbowPattern() {
		curPattern = RAINBOW;
		cyclePosition = 0;
	}

	void rainbowPatternUpdate() {
		if (checkTime(100)) {
			fill_rainbow( leds, NUM_LEDS, gHue++, 7);
			FastLED.show();
		}
	}

	/* *** Pattern: Strobe *** */
	void strobePattern() {
		curPattern = STROBE;
		cyclePosition = 0;
	}

	void strobePatternUpdate() {
		if (checkTime(50)) {
			if (cyclePosition < 20 && cyclePosition % 2 == 0) { 
				for( uint16_t i = 0; i<NUM_LEDS; i++){
					leds[i] = CRGB(0xff, 0xff, 0xff);
				}
			}
			FastLED.show();
			fadeall(90);
			if (cyclePosition + 1 < 50) {
				cyclePosition++;
			} else {
				cyclePosition = 0;
			}
		}
	}

	/* *** Pattern: Surge *** */
	void surgePattern() {
		curPattern = SURGE;
		cyclePosition = 0;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}

	void surgePatternUpdate() {
		if (checkTime(100)) {
			for( uint16_t j = 0; j < NUM_LEDS; j++) {
				if (cyclePosition < 10) { 
					leds[j].nscale8(200);
				} else {
					leds[j] += leds[j].scale8(250);
				}
			}
			FastLED.show();
			if (cyclePosition  < 20) {
				cyclePosition++;
			} else {
				cyclePosition = 0;
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
}
