#include <Wire.h>
#include "badge.h"
#include "i2c.h"

/*
	i2c.cpp -- part of the VegasBadge2018 project.
	Implementation of I2C functions
*/

/* *** I2C *** */
namespace I2C {

	uint8_t error, address;
	uint8_t nDevices;

	void SetupI2C() {
		Wire.begin();
	}

	void Scan() {
		nDevices = 0;

		MySUI.println(F("Scanning..."));
		MySUI.println(F("       0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f"));
		MySUI.print(  F("0x00:   "));
		for(uint8_t address = 1; address < 127; address++ ) {
			Wire.beginTransmission(address);
			error = Wire.endTransmission();

			if (address%16 == 0) {
				MySUI.println();
				MySUI.print(F("0x"));
				MySUI.print(address,HEX);
				MySUI.print(F(":"));
			}
			if (error == 0) {
				if (address<16)
					MySUI.print(" 0");
				else
					MySUI.print(" ");
				MySUI.print(address,HEX);

				nDevices++;
			} else if (error==4) {
				MySUI.print(" xx");
			} else {
				MySUI.print(" --");
			}
		}
		MySUI.println();
		if (nDevices == 0)
			MySUI.println("No I2C devices found\n");
		else
			MySUI.println("done\n");

	}

}
