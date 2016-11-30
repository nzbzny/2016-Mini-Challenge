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
  Track();
  void openBottom();
  void closeBottom();
  void openTop();
  void closeTop();

public:
  Pneumatics bottomTrack;
  Pneumatics topTrack;
};

#endif
