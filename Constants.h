#ifndef SRC_CONSTANTS_H
#define SRC_CONSTANTS_H

namespace Constants {
	//Drive Pins
	static constexpr int driveLeftPin	= 1;
	static constexpr int driveRightPin	= 0;
	static constexpr int driveStickChannel = 0;

	//Sensors
	static constexpr int frontUltrasonicPin = 99;
	static constexpr int backUltrasonicPin = 98;
	static constexpr int ultrasonicVoltageToInches = 148;
	static constexpr int minDistanceToCheeseballs = 12;

	//Pneumatics
	static constexpr int compressorPin = 99; //compressor canbus number

	//Joysticks
	static constexpr int PS4LeftJoystick = 1;
	static constexpr int PS4RightJoystick = 5;
	static constexpr int L2 = 3;
}

#endif
