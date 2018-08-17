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

	bool claptrapStatus = false;
	unsigned long previousClaptrapMillis = 0;
	uint8_t claptrapPosition = 0;

	void SetupI2C() {
		Wire.begin();
	}

	void SetupClapTrap() {
		MySUI.println(F("Setting up ClapTrap"));
		Wire.beginTransmission(0x20);
		Wire.write(0x00); // IODIRA register
		Wire.write(0x00); // set entire PORT A to output
		Wire.endTransmission();

		Wire.beginTransmission(0x20);
		Wire.write(0x01); // IODIRB register
		Wire.write(0x00); // set entire PORT B to output
		Wire.endTransmission();

		claptrapStatus = true;
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

	uint8_t checkClapTrapTime ( uint16_t duration ) {
		uint32_t curMillis = millis();
		if( curMillis - previousClaptrapMillis >= duration) {
			previousClaptrapMillis = curMillis;
			return true;
		} else {
			return false;
		}
	}

	void claptrapUpdate() {
		uint8_t l = 0;
		if (checkClapTrapTime(100)) {
			//MySUI.println("ClapTrap time!\n");
			switch(claptrapPosition) {
				case 0:
					l = 0b00000000;
					break;
				case 1:
					l = 0b00000001;
					break;
				case 2:
					l = 0b00000010;
					break;
				case 3:
					l = 0b00000100;
					break;
				case 5:
					l = 0b00010000;
					break;
				case 6:
					l = 0b00100000;
					break;
				case 7:
					l = 0b10000000;
					break;
				case 8:
					l = 0b01000000;
					break;
			}

			Wire.beginTransmission(0x20);
			Wire.write(0x13); // address port B
			Wire.write(l);  // value to send
			Wire.endTransmission();

			if (claptrapPosition < 9) {
				claptrapPosition++;
			} else {
				claptrapPosition = 0;
			}
		}
	}

	void UpdateI2CPattern() {
		if(claptrapStatus == true) {
			claptrapUpdate();
		}
	}

}
