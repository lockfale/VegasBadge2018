#include <EEPROMex.h>
#include "badge.h"
#include "savecfg.h"
#include "neo.h"

/*
	savecfg.cpp -- part of the VegasBadge2018 project.
	Implementation of EEPROM config functions
*/

/* *** SaveCFG *** */
namespace CFG {

	int versionLength = 7;

	// badgeVersion = major version, minor version, year, month, day, hour, min
	byte badgeVersion[] = {1, 0, 18, 8 , 7 , 9 , 7 };

	uint8_t cfgVersion;
	uint8_t cfgColorID;
	uint8_t cfgPatternID;
	uint8_t cfgMode;
	uint8_t cfgBrightness;

	void SetupCfg() {
		byte localVersion[versionLength];

		cfgVersion = EEPROM.getAddress(sizeof(byte)*versionLength);
		cfgColorID = EEPROM.getAddress(sizeof(byte));
		cfgPatternID = EEPROM.getAddress(sizeof(byte));
		cfgMode = EEPROM.getAddress(sizeof(byte));
		cfgBrightness = EEPROM.getAddress(sizeof(byte));

		EEPROM.readBlock<byte>(cfgVersion, localVersion, versionLength);
		if (memcmp(localVersion, badgeVersion, versionLength) != 0) {
			// New badge version ... initialize EEProm
			EEPROM.updateBlock<byte>(cfgVersion, badgeVersion, versionLength);

			UpdateColorID(0);
			UpdatePatternID(0);
			UpdateMode(1);
			UpdateBrightness(255);

		}
	}

	uint8_t ReadColorID()
	{
		return EEPROM.read(cfgColorID);
	}

	bool UpdateColorID(uint8_t id)
	{
		return EEPROM.updateByte(cfgColorID, id);
	}

	uint8_t ReadPatternID()
	{
		return EEPROM.read(cfgPatternID);
	}

	bool UpdatePatternID(uint8_t id)
	{
		return EEPROM.updateByte(cfgPatternID, id);
	}

	uint8_t ReadMode()
	{
		return EEPROM.read(cfgMode);
	}

	bool UpdateMode(uint8_t id)
	{
		return EEPROM.updateByte(cfgMode, id);
	}

	uint8_t ReadBrightness()
	{
		return EEPROM.read(cfgBrightness);
	}

	bool UpdateBrightness(uint8_t id)
	{
		return EEPROM.updateByte(cfgBrightness, id);
	}

	void PrintEEPROM(void) {
		NEO::PrintColor();
		NEO::PrintPattern();
		NEO::PrintMode();
		NEO::PrintBrightness();
	}

	void PrintVERSION(void) {
		MySUI.print("Version: ");
		MySUI.println(VERSION);
	}
}
