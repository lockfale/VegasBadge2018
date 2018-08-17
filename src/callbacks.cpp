/*
	callbacks.cpp -- part of the VegasBadge2018 project.
	Implementation of callbacks
*/


/* we need the SerialUI lib */
#include <SerialUI.h>
#include "bsettings.h"

/* our project specific types and functions are here */
#include "badge.h"
#include "bbutton.h"
#include "neo.h"
#include "i2c.h"

void doMaintenanceStuff()
{
	/* Here is where we will make updates for each loop */
	Button::UpdateButton();
	NEO::UpdateNeo();
	I2C::UpdateI2CPattern();

}



// "heartbeat" function, called periodically while connected
void CustomHeartbeatCode () {

	// will be called when a user is present.
	doMaintenanceStuff();

}
