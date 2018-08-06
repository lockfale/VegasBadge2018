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
	void PrintEEPROM(void);

}

#endif
