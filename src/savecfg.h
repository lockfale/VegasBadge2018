#ifndef _Badge_SaveCFG_h
#define _Badge_SaveCFG_h

/*
	savecfg.h -- part of the VegasBadge2018 project.
	Function declarations for saving config to EEProm
*/
namespace CFG {

	void SetupCfg();

	uint8_t ReadColorID();
	bool UpdateColorID(uint8_t);
	uint8_t ReadPatternID();
	bool UpdatePatternID(uint8_t);
	uint8_t ReadMode();
	bool UpdateMode(uint8_t);
	uint8_t ReadBrightness();
	bool UpdateBrightness(uint8_t);

	bool ReadClaptrapState();
	bool UpdateClaptrapState(bool);

	void PrintEEPROM(void);
	void PrintVERSION(void);

}

#endif
