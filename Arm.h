/*
 * Arm.h
 *
 *  Created on: October 25, 2016
 *      Author: Noah
 */

#include "WPILib.h"
#include "Constants.h"
#include "Pneumatics.h"

#ifndef SRC_ARM_H
#define SRC_ARM_H

class Arm {
	Pneumatics gripper;
	Talon motor;
	DigitalInput upperSwitch;
	DigitalInput lowerSwitch;

public:
	Arm();
	void raise();
	void lower();
	void stop();
	void grip(bool state);
	bool getGrip();
};

#endif
