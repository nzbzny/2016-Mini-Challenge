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
	//define objects

public:
  Pneumatics(UINT32 InSoleChannel, UINT32 OutSoleChannel);
	void Set();
  void Get();
};

#endif
