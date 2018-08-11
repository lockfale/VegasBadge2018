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
	void ChangeGroovy();

	void UpdateNeo();

	void PrintColor();
	void PrintPattern();

	void PrintMode();
	void switchMode();
	void cycleCurrentMode();

}


#endif
