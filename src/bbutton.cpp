#include <PinButton.h>
#include "badge.h"
#include "bbutton.h"

/*
	bbutton.cpp -- part of the VegasBadge2018 project.
	Implementation of Button functions
*/

/* *** Button *** */
namespace Button {

	PinButton myButton(5);

	void UpdateButton() {
		// Read hardware pin, convert to click events
		myButton.update();

		if (myButton.isSingleClick()) {
			MySUI.println(F("Single button click..."));
		}

		if (myButton.isDoubleClick()) {
			MySUI.println(F("Double button click..."));
		}

	}

}
