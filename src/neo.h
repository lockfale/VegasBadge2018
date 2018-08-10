#ifndef _Badge_Neo_h
#define _Badge_Neo_h

/*
	neo.h -- part of the VegasBadge2018 project.
	Function declarations for all things LEDs
*/
namespace NEO {

	void SetupNeo();

	void ToggleBrightness();
	void PrintBrightness();

	void TurnAllOff();

	void ChangeBlue();
	void ChangeGreen();
	void ChangePink();
	void ChangeRed();
	void ChangeYellow();

	void ChangeChase();
	void ChangeConfetti();
	void ChangePopo();
	void ChangeRainbow();
	void ChangeStrobe();
	void ChangeSurge();
	void ChangeKnightRider();
	void ChangeFire();

	void UpdateNeo();

	void setColor(uint8_t);
	void PrintColor();

	void setPattern(uint8_t);
	void PrintPattern();

	void setColorMode();
	void setPatternMode();
	void setMode(uint8_t);
	void PrintMode();
	void switchMode();
	void cycleCurrentMode();

}


#endif
