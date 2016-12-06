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
	static constexpr int raiseArmButton = 0;
	static constexpr int lowerArmButton = 0;
	static constexpr int grabContainerButton = 0;
	static constexpr int releaseContainerButton = 0;
	static constexpr int releaseBigBallsButton = 0;
	static constexpr int releaseSmallBallsButton = 0;
	static constexpr int releaseAllBallsButton = 0;
	static constexpr int lockBallsButton = 0;

	//Arm
	static constexpr int gripperInSole = 99;
	static constexpr int gripperOutSole = 99;
	static constexpr int armChannel = 99;
	static constexpr int armUpperLimitChannel = 99;
	static constexpr int armLowerLimitChannel = 99;

	//Track
	static constexpr int bottomTrackInSole = 99;
	static constexpr int bottomTrackOutSole = 99;
	static constexpr int topTrackInSole = 99;
	static constexpr int topTrackOutSole = 99;
	static constexpr int trackChannel = 99;
}

#endif
