#ifndef SRC_CONSTANTS_H
#define SRC_CONSTANTS_H

namespace Constants {
	//Drive Pins
	static constexpr int driveLeftPin	= 1; //could need to be switched around TODO: find out
	static constexpr int driveRightPin	= 0; //TODO: find out
	static constexpr int driveStickChannel = 0;

	static constexpr int operatorStickChannel = 1;


	//Sensors
	static constexpr int frontUltrasonicPin = 0;
	static constexpr int backUltrasonicPin = 1;
	static constexpr int ultrasonicVoltageToInches = 148;
	static constexpr int minDistanceToCheeseballs = 12;

	//Pneumatics
	static constexpr int compressorPin = 99; //compressor canbus number TODO: find out

	//Joysticks
	static constexpr int PS4LeftJoystick = 1;
	static constexpr int PS4RightJoystick = 5;
	static constexpr int throttleAxis = 3;
	static constexpr int raiseArmButton = 7;
	static constexpr int lowerArmButton = 8;
	static constexpr int stopArmButton = 9;
	static constexpr int gripOpenButton = 1;
	static constexpr int gripCloseButton = 2;
	static constexpr int topTrackOpenButton = 3;
	static constexpr int topTrackCloseButton = 4;
	static constexpr int bottomTrackOpenButton = 5;
	static constexpr int bottomTrackCloseButton = 6;

	//Arm
	static constexpr int gripperInSole = 4;
	static constexpr int gripperOutSole = 5;
	static constexpr int armChannel = 2;
	static constexpr int armUpperLimitChannel = 0;
	static constexpr int armLowerLimitChannel = 1;

	//Track
	static constexpr int bottomTrackInSole = 0;
	static constexpr int bottomTrackOutSole = 1;
	static constexpr int topTrackInSole = 2;
	static constexpr int topTrackOutSole = 3;

	//DriveTrain
	static constexpr float drivePIDepsilon = 2.0;
	static constexpr float drivePIDMaxSpeed = 0.5;
	static constexpr float drivePIDMinSpeed = 0.1;
	static constexpr float drivePIDFinishTurn = 0.05;
	static constexpr int driveMaxRPM = 590;
	static constexpr float driveK_P = .01;

	//Position
	static constexpr int xStartPos = 0;
	static constexpr int yStartPos = 0;
	static constexpr float gyroOffset = 90;
	static constexpr int ticksPerRotation = 2048;
	static constexpr float quadratureEncoderFactor = .25;
	static constexpr float wheelRadius = 3 * .0254; //meters
}

#endif
