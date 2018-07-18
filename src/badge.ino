/*
	badge.ino -- part of the VegasBadge2018 project.
*/

/* we need the SerialUI lib */
#include <SerialUI.h>
#include "bsettings.h"

/* our project specific types and functions are here */
#include "badge.h"
#include "neo.h"

/* **** standard setup() function **** */
void setup() {
	if (!SetupSerialUI()) {
		DIE_HORRIBLY(F("Problem during setup"));
	}

	// setup FastLED to control NeoPixels
	NEO::SetupNeo();
}


void loop() {

	if (MySUI.checkForUser(heartbeat_function_period_ms)) {

		/* Now we keep handling the serial user's
		** requests until they exit or timeout.
		*/
		while (MySUI.userPresent()) {
			// actually respond to requests, using
			MySUI.handleRequests();
		}
	} else {
		// when no one is connected, we do our 
		// maintenance 'manually'
		doMaintenanceStuff();
	}

}
