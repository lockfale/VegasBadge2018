#ifndef _Badge_I2C_h
#define _Badge_I2C_h

/*
	neo.h -- part of the VegasBadge2018 project.
	Function declarations for all things LEDs
*/
namespace I2C {

	void SetupI2C();
	void SetupClapTrap();
	void Scan();
	void UpdateI2CPattern();
}


#endif
