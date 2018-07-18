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
	SUI::Menu * submen1 = topMenu->subMenu(
		SUI_STR("colors"),
		SUI_STR("Change to solids colors"),
		2);
	if (! submen1 ) { 
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}
	
	SUI::Menu * submen2 = topMenu->subMenu(
		SUI_STR("patterns"),
		SUI_STR("Change LED patterns"),
		2);
	if (! submen2 ) { 
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}
	
	SUI::Menu * submen3 = topMenu->subMenu(
		SUI_STR("i2c"),
		SUI_STR("SOA Communications"),
		2);
	if (! submen3 ) { 
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}
	


	// add everything to the right sub-menu

	/* *** Main Menu -> Colors *** */

	
	if( ! submen1->addCommand(
		SUI_STR("pink"),
		NEO::pinkColor,
		SUI_STR("Make the LEDs pink..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("red"),
		NEO::redColor,
		SUI_STR("Make the LEDs red..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("green"),
		NEO::greenColor,
		SUI_STR("Make the LEDs green..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("blue"),
		NEO::blueColor,
		SUI_STR("Make the LEDs blue..."))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	/* *** Main Menu -> Patterns *** */

	/* *** Main Menu -> I2C *** */
	
	/*
	if( ! submen2->addCommand(
		SUI_STR("Scan"),
		I2C::scan,
		SUI_STR("Scan for SOAs"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	*/
	

	return true;
	
}

