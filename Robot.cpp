#include "Robot.h"

Robot::Robot() :
	position(),
	robotDrive(Constants::driveLeftPin, Constants::driveRightPin, &position),
	arm(),
	track(),
	driveStick(Constants::driveStickChannel),
	operatorStick(Constants::operatorStickChannel),
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
	robotDrive.Enable();

	while(IsOperatorControl() && IsEnabled())
	{
		float throttle = 1;
		//float throttle = driveStick.GetRawAxis(Constants::throttleAxis);
		float leftValue = throttle * driveStick.GetRawAxis(Constants::PS4LeftJoystick);
		float rightValue = throttle * driveStick.GetRawAxis(Constants::PS4RightJoystick);
		float armAngleInput = .3 * -operatorStick.GetRawAxis(1); //left joystick
		armAngleInput = abs(armAngleInput) > 0.005 ? armAngleInput : 0.0;
		arm.move(shooterAngleInput);
		robotDrive.TankDriveSpeed(leftValue, rightValue);

		if (operatorStick.GetRawButton(Constants::gripOpenButton)) {
			arm.grip(true); //TODO: may need to flip
		}
		if (operatorStick.GetRawButton(Constants::gripCloseButton)) {
			arm.grip(false); //TODO: may need to flip
		}
		if (operatorStick.GetRawButton(Constants::topTrackOpenButton)) {
			track.top(true); //TODO: may need to flip
		}
		if (operatorStick.GetRawButton(Constants::topTrackCloseButton)) {
			track.top(false); //TODO: may need to flip
		}
		if (operatorStick.GetRawButton(Constants::bottomTrackOpenButton)) {
			track.bottom(true); //TODO: may need to flip
		}
		if (operatorStick.GetRawButton(Constants::bottomTrackCloseButton)) {
			track.bottom(false); //TODO: may need to flip
		}
	}
	
	robotDrive.Disable();
	compressor.Stop();
	robotDrive.SetSafetyEnabled(true);
}



void Robot::Autonomous() {
	//use navx mxp
	robotDrive.SetSafetyEnabled(false);
	compressor.Start();
	robotDrive.Enable();

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

	arm.grip(true); //may need to flip

	arm.move(.25);

	Wait(1);

	arm.move(0);

	fs = 0;
	while (frontUltrasonic.GetVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,180);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	track.top(false);

	robotDrive.Disable();
	compressor.Stop();
	robotDrive.SetSafetyEnabled(true);
}

START_ROBOT_CLASS(Robot);
