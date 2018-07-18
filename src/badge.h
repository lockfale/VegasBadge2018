#ifndef _Badge_Badge_h
#define _Badge_Badge_h

/*
	badge.h -- part of the VegasBadge2018 project.
	Declarations for everything that was generated...
*/


/* we need the SerialUI lib */
#include <SerialUI.h>

/* MySUI
	Our SerialUI Instance, through which we can send/receive
	data from users.
*/
extern SUI::SerialUI MySUI;

/* custom global scope definitions: */

void doMaintenanceStuff();

/*
	The container for MyInputs, which
	holds all the variables for the various inputs.
*/
typedef struct MyInputsContainerStruct {

	long int LEDPattern;
	// constructor to set sane startup vals
	MyInputsContainerStruct() :
		LEDPattern(0)
	{}
} MyInputsContainerSt;

extern MyInputsContainerSt MyInputs;


// "heartbeat" function, called periodically while connected
void CustomHeartbeatCode();

/* ***** SetupSerialUI: where we'll be setting up menus and such **** */
bool SetupSerialUI();


#define DIE_HORRIBLY(msg)	for(;;){ MySUI.println(msg); delay(1000); }


#endif
