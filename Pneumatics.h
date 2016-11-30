/*
 * Pneumatics.h
 *
 *  Created on: October 25, 2016
 *      Author: Noah
 */

#include "WPILib.h"
#include "Constants.h"

#ifndef SRC_PNEUMATICS_H
#define SRC_PNEUMATICS_H

class Pneumatics {
private:
  DoubleSolenoid pneumaticController;

public:
  Pneumatics(UINT32 InSoleChannel, UINT32 OutSoleChannel):
	  pneumaticController(InSoleChannel, OutSoleChannel)
  {}
  void Set(bool state);
  bool Get();
};

#endif
