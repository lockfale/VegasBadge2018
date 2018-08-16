/*
 * uisetup.cpp -- part of the VegasBadge2018 project.
 * Setup of SerialUI and menu system
 */


/* we need the SerialUI lib */
#include <SerialUI.h>
#include "bsettings.h"

/* our project specific types and functions are here */
#include "badge.h"
#include "neo.h"
#include "i2c.h"
#include "savecfg.h"
#include "bbutton.h"



/* MySUI
 * Our SerialUI Instance, through which we can send/receive
 * data from users. Actually instantiated here, for global use.
 */
SUI::SerialUI MySUI(6);

/*
 * The container for MyInputs, which
 * holds all the variables for the various inputs.
 * Actually instantiated here, for global use.
 */
MyInputsContainerSt MyInputs;


bool SetupSerialUI() {

	// basic SUI setup
	MySUI.setGreeting(F(serial_ui_greeting_str));
	// SerialUI acts just like (is actually a facade for)
	// Serial.  Use _it_, rather than Serial, throughout the
	// program.
	// basic setup of SerialUI:
	MySUI.begin(serial_baud_rate); // serial line open/setup
	MySUI.setTimeout(serial_readtimeout_ms);   // timeout for reads (in ms), same as for Serial.
	MySUI.setMaxIdleMs(serial_maxidle_ms);    // timeout for user (in ms)
	// how we are marking the "end-of-line" (\n, by default):
	MySUI.setReadTerminator(serial_input_terminator);

	// have a "heartbeat" function to hook-up
	MySUI.setUserPresenceHeartbeat(CustomHeartbeatCode);
	// heartbeat_function_period_ms set in main settings header
	MySUI.setUserPresenceHeartbeatPeriod(heartbeat_function_period_ms);

	// Add variable state tracking

	// a few error messages we hopefully won't need

	SUI_FLASHSTRING CouldntCreateMenuErr = F("Could not create menu?");
	SUI_FLASHSTRING CouldntAddItemErr = F("Could not add item?");

	// get top level menu, to start adding items
	SUI::Menu * topMenu = MySUI.topLevelMenu();
	if (! topMenu ) {
		// well, that can't be good...
		MySUI.returnError(F("Very badness in sEriALui!1"));
		return false;
	}



	/* *** Main *** */


	// create all our sub-menus
	SUI::Menu * smcolors = topMenu->subMenu(
		SUI_STR("colors"),
		SUI_STR("Change to solids colors"),
		2);
	if (! smcolors ) {
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}

	SUI::Menu * smpatterns = topMenu->subMenu(
		SUI_STR("patterns"),
		SUI_STR("Change LED patterns"),
		2);
	if (! smpatterns ) {
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}

	SUI::Menu * smi2c = topMenu->subMenu(
		SUI_STR("i2c"),
		SUI_STR("SAO Communications"),
		2);
	if (! smi2c ) {
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}

	SUI::Menu * smpower = topMenu->subMenu(
		SUI_STR("power"),
		SUI_STR("Power Savings"),
		2);
	if (! smpower ) {
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}

	SUI::Menu * smdebug = topMenu->subMenu(
		SUI_STR("debug"),
		SUI_STR("Debug"),
		2);
	if (! smdebug ) {
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}



	// add everything to the right sub-menu

	/* *** Main Menu -> Colors *** */

	if( ! smcolors->addCommand(
		SUI_STR("blue"),
		NEO::ChangeBlue,
		SUI_STR("Turn LEDs blue."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smcolors->addCommand(
		SUI_STR("green"),
		NEO::ChangeGreen,
		SUI_STR("Turn LEDs green."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smcolors->addCommand(
		SUI_STR("pink"),
		NEO::ChangePink,
		SUI_STR("Turn LEDs pink."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smcolors->addCommand(
		SUI_STR("red"),
		NEO::ChangeRed,
		SUI_STR("Turn LEDs red."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smcolors->addCommand(
		SUI_STR("yellow"),
		NEO::ChangeYellow,
		SUI_STR("Turn LEDs yellow."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> Patterns *** */

	if( ! smpatterns->addCommand(
		SUI_STR("chase"),
		NEO::ChangeChase,
		SUI_STR("Chase the LEDs..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("confetti"),
		NEO::ChangeConfetti,
		SUI_STR("Party!!"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("popo"),
		NEO::ChangePopo,
		SUI_STR("Popo coming..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("rainbow"),
		NEO::ChangeRainbow,
		SUI_STR("Taste the rainbow"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("strobe"),
		NEO::ChangeStrobe,
		SUI_STR("Caution, may cause seizures!!"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("surge"),
		NEO::ChangeSurge,
		SUI_STR("Surging blue..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("knight"),
		NEO::ChangeKnightRider,
		SUI_STR("Knight Rider"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("fire"),
		NEO::ChangeFire,
		SUI_STR("Fire.. Fire!!"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("groovy"),
		NEO::ChangeGroovy,
		SUI_STR("Groovy man"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpatterns->addCommand(
		SUI_STR("smoothchase"),
		NEO::ChangeSmoothChase,
		SUI_STR("A smoother chase"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> I2C *** */

	if( ! smi2c->addCommand(
		SUI_STR("scan"),
		I2C::Scan,
		SUI_STR("Scan for SAOs"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> power *** */

	if( ! smpower->addCommand(
		SUI_STR("brightness"),
		NEO::ToggleBrightness,
		SUI_STR("Toggle LED Brightness Level"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpower->addCommand(
		SUI_STR("sleep"),
		Button::sleepNow,
		SUI_STR("Put badge into sleep mode"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smpower->addCommand(
		SUI_STR("print"),
		NEO::PrintBrightness,
		SUI_STR("Print Power Configuration"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	/* *** Main Menu -> Debug *** */

	if( ! smdebug->addCommand(
		SUI_STR("eeprom"),
		CFG::PrintEEPROM,
		SUI_STR("Print EEPROM settings"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	if( ! smdebug->addCommand(
		SUI_STR("version"),
		CFG::PrintVERSION,
		SUI_STR("Print firmware version"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	return true;

}

