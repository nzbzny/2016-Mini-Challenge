#include "Robot.h"

Robot::Robot() :
	position(),
	robotDrive(Constants::driveLeftPin, Constants::driveRightPin, &position),
	arm(),
	track(),
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

	track.bottom(!track.getBottom());

	while(IsOperatorControl() && IsEnabled())
	{
		float throttle = driveStick.GetRawAxis(Constants::throttleAxis);
		float leftValue = throttle * driveStick.GetRawAxis(Constants::PS4LeftJoystick);
		float rightValue = throttle * driveStick.GetRawAxis(Constants::PS4RightJoystick);
		robotDrive.TankDriveSpeed(leftValue, rightValue);
		if (driveStick.GetRawButton(Constants::raiseArmButton))
			arm.raise();
		if (driveStick.GetRawButton(Constants::lowerArmButton))
			arm.lower();
		if (driveStick.GetRawButton(Constants::gripButton)) {
			arm.grip(!arm.getGrip()); //TODO: may need to flip
		}
		if (driveStick.GetRawButton(Constants::topTrackButton)) {
			track.top(!track.getTop()); //TODO: may need to flip
		}
		if (driveStick.GetRawButton(Constants::bottomTrackButton)) {
			track.bottom(!track.getBottom()); //TODO: may need to flip
		}
	}

	compressor.Stop();
	robotDrive.SetSafetyEnabled(true);
}



void Robot::Autonomous() {
	//use navx mxp
	robotDrive.SetSafetyEnabled(false);
	compressor.Start();

	//track.lock();

	int fs = 0;
	while (frontUltrasonic.GetVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,0);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	arm.lower();

	Wait(1);

	arm.stop();

	arm.grip(!arm.getGrip());

	arm.raise();

	Wait(1);

	arm.stop();

	fs = 0;
	while (frontUltrasonic.GetVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,180);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	track.top(!track.getTop());

	compressor.Stop();
	robotDrive.SetSafetyEnabled(true);
}

START_ROBOT_CLASS(Robot);
