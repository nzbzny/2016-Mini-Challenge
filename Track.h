/*
 * Track.h
 *
 *  Created on: October 25, 2016
 *      Author: Noah
 */

#include "WPILib.h"
#include "Constants.h"
#include "Pneumatics.h"

#ifndef SRC_Track_H
#define SRC_Track_H

class Track {
	Pneumatics bottomTrack;
	Pneumatics topTrack;

public:
	Track();
	void bottom(bool state);
	void top(bool state);
	bool getBottom();
	bool getTop();
};

#endif
