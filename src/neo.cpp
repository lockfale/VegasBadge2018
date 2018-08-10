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
	const uint8_t NUM_LEDS = 6;
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
	const uint8_t YELLOW = 5;
	const uint8_t COLORS_NR_ITEMS = 6;

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
	const uint8_t KNIGHT = 7;
	const uint8_t FIRE = 8;
	const uint8_t PATTERNS_NR_ITEMS = 9;

	uint8_t curPattern = 0;

	const uint8_t NO_MODE = 0;
	const uint8_t MODE_COLORS = 1;
	const uint8_t MODE_PATTERNS = 2;

	uint8_t curMode = NO_MODE;

	/******************************************************
	 *
	 * Brightness Functions
	 *
	 ******************************************************/

	void setBrightness() {
		if(CFG::ReadBrightness() == brightnessHigh) {
			FastLED.setBrightness( brightnessHigh );
		} else if(CFG::ReadBrightness() == brightnessLow) {
			FastLED.setBrightness( brightnessLow );
		} else {
			FastLED.setBrightness( brightnessHigh );
			CFG::UpdateBrightness( brightnessHigh );
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

	void SetupNeo() {
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

		setBrightness();

		if ( CFG::ReadMode() == MODE_COLORS ) {
			setColorMode();
			setColor(CFG::ReadColorID());
		} else if ( CFG::ReadMode() == MODE_PATTERNS ) {
			setPatternMode();
			setPattern(CFG::ReadPatternID());
		} else {
			setColorMode();
			setColor(CFG::ReadColorID());
			CFG::UpdateMode(MODE_COLORS);
		}

	}

	void fadeAll(uint8_t value) {
		for( uint8_t j = 0; j < NUM_LEDS; j++) {
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

	void fillAll(CRGB color){
		for( uint8_t i = 0; i<NUM_LEDS; i++){
			leds[i] = color;
		}
		FastLED.show();
	}

	void TurnAllOff() {
		curMode = NO_MODE;
		fillAll(CRGB::Black);
	}

	/******************************************************
	 *
	 * Colors
	 *
	 ******************************************************/

	/* *** Color: Pink *** */
	void ChangePink() {
		setColor(PINK);
	}

	/* *** Color: Red *** */
	void ChangeRed() {
		setColor(RED);
	}

	/* *** Color: Green *** */
	void ChangeGreen() {
		setColor(GREEN);
	}

	/* *** Color: Blue *** */
	void ChangeBlue() {
		setColor(BLUE);
	}

	/* *** Color: Yellow *** */
	void ChangeYellow() {
		setColor(YELLOW);
	}

	void setColor(uint8_t c) {
		CRGB colorRGB;

		setMode(MODE_COLORS);
		setBrightness();

		if ( c >= COLORS_NR_ITEMS ) {
			curColor = 1;
		} else {
			curColor = c;
		}

		if ( curColor > NO_COLOR ) {
			CFG::UpdateColorID(curColor);
		}

		switch (curColor) {
			case PINK:
				curColor = PINK;
				colorRGB = CRGB(0xff, 0x14, 0x93);
				break;
			case RED:
				curColor = RED;
				colorRGB = CRGB::Red;
				break;
			case GREEN:
				curColor = GREEN;
				colorRGB = CRGB::Green;
				break;
			case BLUE:
				curColor = BLUE;
				colorRGB = CRGB::Blue;
				break;
			case YELLOW:
				curColor = YELLOW;
				colorRGB = CRGB::Yellow;
				break;
		}
		fillAll(colorRGB);
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
			case YELLOW:
				MySUI.println("Yellow");
				break;
		}
	}

	void cycleColor() {
		curColor += 1;
		setColor(curColor);
	}

	/******************************************************
	 *
	 * Patterns
	 *
	 ******************************************************/

	/* *** Pattern: Chase *** */
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
	void ChangeConfetti() {
		setPattern(CONFETTI);
	}

	void confettiPatternUpdate() {
		if (checkTime(50)) {
			uint8_t pos = random8(NUM_LEDS);
			leds[pos] = CHSV(gHue + random8(64), 200, 255);
			FastLED.show();
			fadeAll(80);
		}
	}

	/* *** Pattern: Popo *** */
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
	void ChangeStrobe() {
		setPattern(STROBE);
	}

	void strobePatternUpdate() {
		if (checkTime(50)) {
			if (patternPosition < 20 && patternPosition % 2 == 0) {
				for( uint8_t i = 0; i<NUM_LEDS; i++){
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
	void ChangeSurge() {
		setPattern(SURGE);
	}

	void surgePatternUpdate() {
		if (checkTime(100)) {
			for( uint8_t j = 0; j < NUM_LEDS; j++) {
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

	/* *** Pattern: Knight Rider *** */
	void ChangeKnightRider() {
		setPattern(KNIGHT);
	}

	void knightRiderPatternUpdate() {
		if (checkTime(150)) {
			if (patternPosition == 0) {
				leds[0] = CRGB::Red;
				leds[5] = CRGB::Red;
			} else if (patternPosition == 1 || patternPosition == 3) {
				leds[1] = CRGB::Red;
				leds[4] = CRGB::Red;
			} else if (patternPosition == 2) {
				leds[2] = CRGB::Red;
				leds[3] = CRGB::Red;
			}
			leds[patternPosition] = CRGB::Red;
			FastLED.show();
			fadeAll(90);
			if (patternPosition < 3) {
				patternPosition++;
			} else {
				patternPosition = 0;
			}
		}
	}

	/* *** Pattern: Fire *** */
	// COOLING: How much does the air cool as it rises?
	// Less cooling = taller flames.  More cooling = shorter flames.
	// Default 55, suggested range 20-100
	#define COOLING  20

	// SPARKING: What chance (out of 255) is there that a new spark will be lit?
	// Higher chance = more roaring fire.  Lower chance = more flickery fire.
	// Default 120, suggested range 50-200.
	#define SPARKING 170
	void ChangeFire() {
		setPattern(FIRE);
	}

	void firePatternUpdate() {
		// Array of temperature readings at each simulation cell
		static byte heat[NUM_LEDS];

		// Step 1.  Cool down every cell a little
		for( uint8_t i = 0; i < NUM_LEDS; i++) {
			heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for( uint8_t k= NUM_LEDS - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if( random8() < SPARKING ) {
			int y = random8(7);
			heat[y] = qadd8( heat[y], random8(160,255) );
		}

		// Step 4.  Map from heat cells to LED colors
		for( uint8_t j = 0; j < NUM_LEDS; j++) {
			leds[j] = HeatColor( heat[j]);
		}
		FastLED.show();
	}

	void setPattern(uint8_t p) {
		setMode(MODE_PATTERNS);
		setBrightness();

		if ( p >= PATTERNS_NR_ITEMS ) {
			curPattern = 1;
		} else {
			curPattern = p;
		}

		MySUI.print("Set Pattern: ");
		MySUI.println(curPattern);
		patternPosition = 0;
		CFG::UpdatePatternID(curPattern);
		switch (curPattern) {
			case CHASE:
				curPattern = CHASE;
				break;
			case CONFETTI:
				curPattern = CONFETTI;
				break;
			case POPO:
				curPattern = POPO;
				break;
			case RAINBOW:
				curPattern = RAINBOW;
				break;
			case STROBE:
				curPattern = STROBE;
				break;
			case SURGE:
				curPattern = SURGE;
				fillAll(CRGB::Blue);
				break;
			case KNIGHT:
				curPattern = KNIGHT;
				break;
			case FIRE:
				curPattern = FIRE;
				break;
		}
	}

	/* *** Update function *** */
	void UpdateNeo() {
		if ( curMode == MODE_PATTERNS ) {
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
				case KNIGHT:
					knightRiderPatternUpdate();
					break;
				case FIRE:
					firePatternUpdate();
					break;
			}
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
			case KNIGHT:
				MySUI.println("Knight Rider");
				break;
			case FIRE:
				MySUI.println("Fire");
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
			setPattern(CFG::ReadPatternID());
		} else if ( curMode == MODE_PATTERNS ) {
			setMode(MODE_COLORS);
			setColor(CFG::ReadColorID());
		} else {
			if ( CFG::ReadMode() == MODE_COLORS ) {
				setMode(MODE_COLORS);
				setColor(CFG::ReadColorID());
			} else {
				setMode(MODE_PATTERNS);
				setPattern(CFG::ReadPatternID());
			}
		}
	}

	void cycleCurrentMode() {
		if ( curMode == MODE_COLORS ) {
			cycleColor();
		} else if ( curMode == MODE_PATTERNS ) {
			cyclePattern();
		} else {
			if ( CFG::ReadMode() == MODE_COLORS ) {
				setMode(MODE_COLORS);
				setColor(CFG::ReadColorID());
			} else {
				setMode(MODE_PATTERNS);
				setPattern(CFG::ReadPatternID());
			}
		}
	}
}
