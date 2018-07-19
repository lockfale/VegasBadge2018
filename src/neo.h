#ifndef _Badge_Neo_h
#define _Badge_Neo_h

/*
	neo.h -- part of the VegasBadge2018 project.
	Function declarations for all things LEDs
*/
namespace NEO {

	void SetupNeo();
	void pinkColor();
	void redColor();
	void greenColor();
	void blueColor();

	void chasePattern();
	void confettiPattern();
	void popoPattern();
	void rainbowPattern();
	void strobePattern();
	void surgePattern();

	void UpdateNeo();
}


#endif
