#include <FastLED.h>
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

	void SetupNeo() {
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	}

	void pinkColor() {
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB(0xff, 0x14, 0x93);
			FastLED.show();
		}
	}

	void redColor() {
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Red;
			FastLED.show();
		}
	}

	void greenColor() {
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Green;
			FastLED.show();
		}
	}

	void blueColor() {
		for( uint16_t i = 0; i<NUM_LEDS; i++){
			leds[i] = CRGB::Blue;
			FastLED.show();
		}
	}

}
