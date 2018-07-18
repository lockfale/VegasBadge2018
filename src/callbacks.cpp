/*
	callbacks.cpp -- part of the VegasBadge2018 project.
	Implementation of callbacks
*/


/* we need the SerialUI lib */
#include <SerialUI.h>
#include "bsettings.h"

/* our project specific types and functions are here */
#include "badge.h"

void doMaintenanceStuff()
{
	/* Here is where we will make updates for each loop */

}



// "heartbeat" function, called periodically while connected
void CustomHeartbeatCode () {

	// will be called when a user is present.
	doMaintenanceStuff();

}
