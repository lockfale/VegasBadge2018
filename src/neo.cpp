#include <FastLED.h>
#include "badge.h"
#include "neo.h"
#include "savecfg.h"

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

	uint8_t brightnessLow = 64;
	uint8_t brightnessHigh = 255;

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

	const uint8_t MODE_COLORS = 0;
	const uint8_t MODE_PATTERNS = 1;

	uint8_t curMode = 0;

	void SetupNeo() {
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

		setColor(CFG::ReadColorID());
		setPattern(CFG::ReadPatternID());
		setMode(CFG::ReadMode());
		FastLED.setBrightness( CFG::ReadBrightness() );
	}

	void fadeAll(uint8_t value) {
		for( uint16_t j = 0; j < NUM_LEDS; j++) {
			leds[j].nscale8(value);
		}
	}

	void ToggleBrightness() {
		if(CFG::ReadBrightness() == brightnessHigh) {
			FastLED.setBrightness( brightnessLow );
			CFG::UpdateBrightness( brightnessLow );
		} else {
			FastLED.setBrightness( brightnessHigh );
			CFG::UpdateBrightness( brightnessHigh );
		}
		if ( curMode == MODE_COLORS ) {
			setColor(curColor);
		}
	}

	void PrintBrightness() {
		MySUI.print("Brightness: ");
		MySUI.println(FastLED.getBrightness());
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
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB(0xff, 0x14, 0x93);
		}
		FastLED.show();
	}

	void ChangePink() {
		setColor(PINK);
	}

	void redColor() {
		curColor = RED;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Red;
		}
		FastLED.show();
	}

	void ChangeRed() {
		setColor(RED);
	}

	void greenColor() {
		curColor = GREEN;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Green;
		}
		FastLED.show();
	}

	void ChangeGreen() {
		setColor(GREEN);
	}

	void blueColor() {
		curColor = BLUE;
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}

	void ChangeBlue() {
		setColor(BLUE);
	}

	/* *** Pattern: Chase *** */
	void initChasePattern() {
		curPattern = CHASE;
	}

	void ChangeChase() {
		setPattern(CHASE);
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
	void initConfettiPattern() {
		curPattern = CONFETTI;
	}

	void ChangeConfetti() {
		setPattern(CONFETTI);
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
	void initPopoPattern() {
		curPattern = POPO;
	}

	void ChangePopo() {
		setPattern(POPO);
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
	void initRainbowPattern() {
		curPattern = RAINBOW;
	}

	void ChangeRainbow() {
		setPattern(RAINBOW);
	}

	void rainbowPatternUpdate() {
		if (checkTime(50)) {
			fill_rainbow( leds, NUM_LEDS, gHue++, 7);
			FastLED.show();
		}
	}

	/* *** Pattern: Strobe *** */
	void initStrobePattern() {
		curPattern = STROBE;
	}

	void ChangeStrobe() {
		setPattern(STROBE);
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
	void initSurgePattern() {
		curPattern = SURGE;

		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
		}
		FastLED.show();
	}

	void ChangeSurge() {
		setPattern(SURGE);
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

	void setColor(uint8_t c) {
		setColorMode();
		if ( c >= COLORS_NR_ITEMS ) {
			curColor = 1;
		} else {
			curColor = c;
		}

		CFG::UpdateColorID(curColor);
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

	void PrintColor() {
		uint8_t c = CFG::ReadColorID();

		MySUI.print("Color: ");
		switch (c) {
			case PINK:
				MySUI.println("Pink");
				break;
			case RED:
				MySUI.println("Red");
				break;
			case GREEN:
				MySUI.println("Green");
				break;
			case BLUE:
				MySUI.println("Blue");
				break;
		}
	}

	void cycleColor() {
		curColor += 1;
		setColor(curColor);
	}

	void setPattern(uint8_t p) {
		setPatternMode();
		if ( p >= PATTERNS_NR_ITEMS ) {
			curPattern = 1;
		} else {
			curPattern = p;
		}

		patternPosition = 0;
		CFG::UpdatePatternID(curPattern);
		switch (curPattern) {
			case CHASE:
				initChasePattern();
				break;
			case CONFETTI:
				initConfettiPattern();
				break;
			case POPO:
				initPopoPattern();
				break;
			case RAINBOW:
				initRainbowPattern();
				break;
			case STROBE:
				initStrobePattern();
				break;
			case SURGE:
				initSurgePattern();
				break;
		}
	}

	void PrintPattern() {
		uint8_t p = CFG::ReadPatternID();

		MySUI.print("Pattern: ");
		switch (p) {
			case CHASE:
				MySUI.println("Chase");
				break;
			case CONFETTI:
				MySUI.println("Confetti");
				break;
			case POPO:
				MySUI.println("Popo");
				break;
			case RAINBOW:
				MySUI.println("Rainbow");
				break;
			case STROBE:
				MySUI.println("Strobe");
				break;
			case SURGE:
				MySUI.println("Surge");
				break;
		}
	}

	void cyclePattern() {
		curPattern += 1;
		setPattern(curPattern);
	}

	void setColorMode() {
		curMode = MODE_COLORS;
		curPattern = NO_PATTERN;
	}

	void setPatternMode() {
		curMode = MODE_PATTERNS;
		curColor = NO_COLOR;
	}

	void setMode(uint8_t m) {
		if ( m == MODE_COLORS ) {
			setColorMode();
			CFG::UpdateMode(MODE_COLORS);
		} else if ( m == MODE_PATTERNS ) {
			setPatternMode();
			CFG::UpdateMode(MODE_PATTERNS);
		} else {
			setColorMode();
			CFG::UpdateMode(MODE_COLORS);
		}
	}

	void PrintMode() {
		uint8_t m = CFG::ReadMode();

		MySUI.print("Mode: ");
		switch (m) {
			case MODE_COLORS:
				MySUI.println("Colors");
				break;
			case MODE_PATTERNS:
				MySUI.println("Patterns");
				break;
		}
	}

	void switchMode() {
		if ( curMode == MODE_COLORS ) {
			setMode(MODE_PATTERNS);
		} else {
			setMode(MODE_COLORS);
		}
	}

	void cycleMode() {
		if ( curMode == MODE_COLORS ) {
			cycleColor();
		} else {
			cyclePattern();
		}
	}

}
