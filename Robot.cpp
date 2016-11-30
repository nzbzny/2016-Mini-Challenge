#include "Robot.h"

Robot::Robot() :
	position(),
	robotDrive(Constants::driveLeftPin, Constants::driveRightPin, position),
	driveStick(Constants::driveStickChannel),
	frontUltrasonic(Constants::frontUltrasonicPin),
	backUltrasonic(Constants::backUltrasonicPin),
	compressor(Constants::compressorPin) //canbus number
{
	robotDrive.SetExpiration(0.1); //safety feature
}

void Robot::OperatorControl() //teleop code
{
	robotDrive.SetSafetyEnabled(false);
	compressor.Start();

	//track.releaseSmallBalls();

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

	//track.lock();

	int fs = 0;
	while (frontUltrasonic.getVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,0);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	//arm.down();

	//gripper.grab();

	//arm.up(); (separate thread probably)

	Wait(1);//Temporary so robot doesn't flip

	fs = 0;
	while (frontUltrasonic.getVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,180);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	//track.releaseBigBalls();

	compressor.Stop();
}

START_ROBOT_CLASS(Robot);
