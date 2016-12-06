#include "Robot.h"

Robot::Robot() :
	position(),
	robotDrive(Constants::driveLeftPin, Constants::driveRightPin, position),
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

	track.openBottom();

	while(IsOperatorControl() && IsEnabled())
	{
		float leftValue = throttle * driveStick.GetRawAxis(Constants::PS4LeftJoystick);
		float rightValue = throttle * driveStick.GetRawAxis(Constants::PS4RightJoystick);
		robotDrive.TankDriveSpeed(leftValue, rightValue);
		if (driveStick.getRawButton(Constants::raiseArmButton))
			arm.raise();
		if (driveStick.getRawButton(Constants::lowerArmButton))
			arm.lower();
		if (driveStick.getRawButton(Constants::grabContainerButton))
			arm.close();
		if (driveStick.getRawButton(Constants::releaseContainerButton))
			arm.open();
		if (driveStick.getRawButton(Constants::releaseBigBallsButton))
			track.openTop();
		if (driveStick.getRawButton(Constants::releaseSmallBallsButton))
			track.openBottom();
		if (driveStick.getRawButton(Constants::releaseAllBallsButton))
			{
				track.openTop();
				track.openBottom();
			}
		if (driveStick.getRawButton(Constants::lockBallsButton))
			{
				track.closeTop();
				track.closeBottom();
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
	while (frontUltrasonic.getVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,0);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	arm.lower();
	
	arm.stop();

	gripper.close();

	arm.raise();
	
	arm.stop();

	fs = 0;
	while (frontUltrasonic.getVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,180);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	track.openTop();

	compressor.Stop();
	robotDrive.SetSafetyEnabled(true);
}

START_ROBOT_CLASS(Robot);
