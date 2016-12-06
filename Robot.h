#include "WPILib.h"

#include "Constants.h"
#include "Arm.h"
#include "DriveTrain.h"
#include "Position.h"
#include "Track.h"

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

class Robot : public SampleRobot { 
	DriveTrain robotDrive;
	Arm arm;
	Track track;
	Position position;
	Joystick driveStick;
	AnalogInput frontUltrasonic, backUltrasonic;
	Compressor compressor;
public:
	Robot();
	void OperatorControl();
	void Autonomous();
};

#endif /* SRC_ROBOT_H_ */
