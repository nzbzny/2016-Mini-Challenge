#include "Robot.h"

Robot::Robot() :
	robotDrive(Constants::driveLeftPin, Constants::driveRightPin),
	driveStick(Constants::driveStickChannel),
	ultrasonic(Constants::ultrasonicPin),
	compressor(Constants::compressorPin) //canbus number
{
	robotDrive.SetExpiration(0.1); //safety feature
}

void Robot::OperatorControl() //teleop code
{
	robotDrive.SetSafetyEnabled(false);
	compressor.Start();

	while(IsOperatorControl() && IsEnabled())
	{
		float leftValue = throttle * driveStick.GetRawAxis(Constants::PS4LeftJoystick);
		float rightValue = throttle * driveStick.GetRawAxis(Constants::PS4RightJoystick);
		robotDrive.TankDrive(leftValue, rightValue, true);
	}

	compressor.Stop();
}

void Robot::Autonomous() {
	//use navx mxp
	compressor.Start();
	float distanceToCheezeBalls;
	distanceToCheezeBalls = ultrasonic.GetVoltage(); //multiply by whatever the factor constant is - will probably need to be found through testing if I remember correctly

	robotDrive.TankDriveStraight(0,0); //float speed, float fieldAngle


	//do stuff

	compressor.Stop();
}

START_ROBOT_CLASS(Robot);
