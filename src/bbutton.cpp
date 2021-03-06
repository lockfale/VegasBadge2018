#include <avr/sleep.h>
#include <PinButton.h>
#include "badge.h"
#include "bbutton.h"
#include "neo.h"

/*
	bbutton.cpp -- part of the VegasBadge2018 project.
	Implementation of Button functions
*/

/* *** Button *** */
namespace Button {

	PinButton myButton(5);

	void sleepNow () {
		MySUI.println(F("[+] Going to sleep"));
		NEO::TurnAllOff();

		delay(1000);

		set_sleep_mode (SLEEP_MODE_PWR_DOWN);
		sleep_enable ();
		sleep_mode();

	}

	void UpdateButton() {
		// Read hardware pin, convert to click events
		myButton.update();

		if (myButton.isSingleClick()) {
			MySUI.println(F("Detected Single Press..."));
			MySUI.println(F("[+] Cycle in current mode."));
			NEO::cycleCurrentMode();
		}

		if (myButton.isDoubleClick()) {
			MySUI.println(F("Detected Double Press..."));
			MySUI.println(F("[+] Switching modes"));
			NEO::switchMode();
		}

		if (myButton.isLongClick()) {
			MySUI.println(F("Detected Long Press..."));
			MySUI.println(F("[+] Turning off LEDS"));

			sleepNow();
		}

	}

}
