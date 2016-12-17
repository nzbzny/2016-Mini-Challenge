#include "DriveTrain.h"
#define PI 3.14159265

DriveTrain::DriveTrain(uint32_t leftMasterDeviceID, uint32_t leftSlaveDeviceID, uint32_t rightMasterDeviceID, uint32_t rightSlaveDeviceID, Position *position_):
	RobotDrive(leftMaster, rightMaster),
	leftMaster(leftMasterDeviceID),
	leftSlave(leftSlaveDeviceID),
	rightMaster(rightMasterDeviceID),
	rightSlave(rightSlaveDeviceID),
	position(position_)
{
	leftMaster.SetClosedLoopOutputDirection(true);
	leftMaster.SetControlMode(CANTalon::ControlMode::kSpeed);
	leftMaster.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	leftMaster.ConfigEncoderCodesPerRev(2048);
	leftMaster.SetSensorDirection(true);
	leftMaster.SelectProfileSlot(0);
	leftMaster.SetF(0.124);
	leftMaster.SetP(0.12);
	leftMaster.SetI(0.00000);
	leftMaster.SetD(0.0);
	leftMaster.SetAllowableClosedLoopErr(10);
	leftMaster.SetInverted(false);

	leftSlave.SetModeSelect(CanTalonSRX::kMode_SlaveFollower);
	leftSlave.SetDemand(leftMasterDeviceID);
	leftSlave.SetRevMotDuringCloseLoopEn(1);

	rightMaster.SetControlMode(CANTalon::ControlMode::kSpeed);
	rightMaster.SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	rightMaster.ConfigEncoderCodesPerRev(2048);
	rightMaster.SetSensorDirection(true);
	rightMaster.SelectProfileSlot(0);
	rightMaster.SetF(0.124);
	rightMaster.SetP(0.12);
	rightMaster.SetI(0.0000);
	rightMaster.SetD(0.0);
	rightMaster.SetAllowableClosedLoopErr(10);
	rightMaster.SetInverted(true);

	rightSlave.SetModeSelect(CanTalonSRX::kMode_SlaveFollower);
	rightSlave.Set(rightMasterDeviceID);
	rightSlave.SetDemand(rightMasterDeviceID);

	SmartDashboard::PutNumber("Min Motor Power", Constants::drivePIDMinSpeed);
}

DriveTrain::DriveTrain(uint32_t leftMotorID, uint32_t rightMotorID, Position *position_) :
	RobotDrive(leftMaster, rightMaster),
	leftMaster(leftMotorID),
	rightMaster(rightMotorID),
	position(position_)
{
	leftMaster.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	rightMaster.SetControlMode(CANTalon::ControlMode::kPercentVbus);
}

void DriveTrain::Enable()
{
	leftMaster.Enable();
	rightMaster.Enable();
}

void DriveTrain::Disable()
{
	leftMaster.Disable();
	rightMaster.Disable();
}

void DriveTrain::TurnToAngle(float absAngle)
{
	std::ofstream logfile;
	logfile.open("/home/lvuser/logfile.txt", std::ofstream::out);
	if (!logfile)
	{
		SmartDashboard::PutString("status", "Failed to open logfile");
		return;
	}
	SmartDashboard::PutString("status", "TurnToAngle turn started");

	float k_P = 0.01;

	// Convert target to +/- 180 degrees to match gyro
	float targetAngle = (absAngle <= 180.0) ? absAngle : absAngle-360;
	float currentAngle = position->GetAngleDegrees();
	float error = targetAngle-currentAngle;

	// Take the shortest path to targetAngle
	error = (error > 180) ? error - 360 : error;
	error = (error < -180) ? error + 360 : error;

	auto scaleOutput = [](float output)
	{
		bool tooLowAndNonZero = abs(output) > Constants::drivePIDMinSpeed
			&& abs(output) < Constants::drivePIDFinishTurn;
		bool tooHigh = abs(output) > Constants::drivePIDMaxSpeed;

		if (tooLowAndNonZero)
			output = copysign(Constants::drivePIDFinishTurn, output);
		if (tooHigh)
			output = copysign(Constants::drivePIDMaxSpeed, output);

		return output;
	};

	SmartDashboard::PutNumber("targetAngle", targetAngle);
	SmartDashboard::PutNumber("errorAngle", error);

	unsigned int failsafe = 0;
	float delta_t = 0.02;
	unsigned int failsafeMax = static_cast<unsigned int>(3.0 / delta_t); // Two seconds timeout

	while(abs(error) > Constants::drivePIDepsilon && failsafe <= failsafeMax)
	{
		float motorOutput = scaleOutput(k_P * error);
		SmartDashboard::PutNumber("TurnPower", motorOutput);
		TankDriveSpeed(motorOutput, -motorOutput);

		Wait(delta_t);
		failsafe++;

		currentAngle = position->GetAngleDegrees();
		error = targetAngle - currentAngle;
		error = (abs(error) > 180) ? error - copysign(360.0, error) : error;

		SmartDashboard::PutNumber("ErrorAngle", abs(error));
		logfile << "Target Angle: "  << targetAngle <<
		           ", Gyro Angle: "  << currentAngle <<
				   ", Motor Power: " << motorOutput << std::endl;

	if (failsafe >= failsafeMax)
	{
		SmartDashboard::PutString("status", "driveTrain.TurnToAngle() failsafe hit");
		SmartDashboard::PutBoolean("failsafe", false);
		logfile << "Failsafe hit!" << std::endl;
		TankDriveSpeed(0, 0);
		return;
	}
	else
	{
		SmartDashboard::PutString("status", "driveTrain.TurnToAngle() completed");
		SmartDashboard::PutBoolean("failsafe", true);
		logfile << "Successfully completed turn." << std::endl;
	}
	}
	TankDriveSpeed(0, 0);
}

void DriveTrain::TurnToRelativeAngle(float angle)
{
	AutoTurnToAngle(fmod(angle + position->GetAngleDegreesPositive(), 360));
}

void DriveTrain::TankDriveStraight(float speed, float fieldAngle)
{
	// Convert target to +/- 180 degrees to match gyro
	float targetAngle = (fieldAngle <= 180.0) ? fieldAngle : fieldAngle-360;
	float currentAngle = position->GetAngleDegrees();
	float error = targetAngle-currentAngle;

	// Take the shortest path to targetAngle
	error = (error > 180) ? error - 360 : error;
	error = (error < -180) ? error + 360 : error;

	float pidAdjustment = Constants::driveK_P * error;

	bool tooLowAndNonZero = abs(pidAdjustment) > Constants::drivePIDMinSpeed
		&& abs(pidAdjustment) < Constants::drivePIDFinishTurn;
	bool tooHigh = abs(pidAdjustment) > Constants::drivePIDMaxSpeed;

	if (tooLowAndNonZero)
		pidAdjustment = copysign(Constants::drivePIDFinishTurn, pidAdjustment);
	if (tooHigh)
		pidAdjustment = copysign(Constants::drivePIDMaxSpeed, pidAdjustment);

	float motorOutput;
	if (abs(error) > 20.0)
		TankDriveSpeed(pidAdjustment, -pidAdjustment);
	else
		TankDriveSpeed(speed + pidAdjustment, speed - pidAdjustment);
}

void DriveTrain::TankDriveSpeed(float leftspeed, float rightspeed)
{
	leftspeed = (std::abs(leftspeed) <= Constants::drivePIDMinSpeed) ? 0.0 : leftspeed;
	rightspeed = (std::abs(rightspeed) <= Constants::drivePIDMinSpeed) ? 0.0 : rightspeed;
	leftMaster.SetControlMode(CANTalon::ControlMode::kSpeed);
	rightMaster.SetControlMode(CANTalon::ControlMode::kSpeed);
	leftMaster.Set(leftspeed * Constants::driveMaxRPM);
	rightMaster.Set(rightspeed * Constants::driveMaxRPM);
	SmartDashboard::PutNumber("LeftError", leftMaster.GetClosedLoopError());
	SmartDashboard::PutNumber("RightError", rightMaster.GetClosedLoopError());
}

/*void DriveTrain::AutoTurnToAngle(float angle) {
	leftMaster.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	rightMaster.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	float p = (Constants::autoTurnMaxPwr - Constants::autoTurnMinPwr) * 100 / (Constants::autoTurnMaxAngle - Constants::autoTurnMinAngle);
	float error = CalculateAutoTurnError(angle);
	int errorMultiplier = 1; //1 or -1 to determine which way to turn
	if (error < 0) {
		error = -1 * error;
		errorMultiplier = -1;
	}
	int speed;
	while (error > Constants::autoTurnMaxAngle) {
		SmartDashboard::PutString("Auto Turn Loop", "Greater than max");
		error = CalculateAutoTurnError(angle);
		SmartDashboard::PutNumber("Auto Turn Error", error);
		speed = Constants::autoTurnMaxPwr * errorMultiplier;
		SmartDashboard::PutNumber("Auto Turn Speed", speed);
		TankDriveSpeed(speed, -1 * speed);
	}
	while (error > Constants::autoTurnMinAngle && error < Constants::autoTurnMaxAngle) {
		SmartDashboard::PutString("Auto Turn Loop", "Between max and min");
		error = CalculateAutoTurnError(angle);
		SmartDashboard::PutNumber("Auto Turn Error", error);
		speed = p * ((error - Constants::autoTurnMinAngle) / 100) + Constants::autoTurnMinPwr * errorMultiplier;
		SmartDashboard::PutNumber("Auto Turn Speed", speed);
		TankDriveSpeed(speed, -1 * speed);
	}
	while (error < Constants::autoTurnMinAngle && error > Constants::autoTurnMinDelta) {
		SmartDashboard::PutString("Auto Turn Loop", "Less than min");
		error = CalculateAutoTurnError(angle);
		SmartDashboard::PutNumber("Auto Turn Error", error);
		speed = Constants::autoTurnMinPwr * errorMultiplier;
		SmartDashboard::PutNumber("Auto Turn Speed", speed);
		TankDriveSpeed(speed, -1 * speed);
	}
	SmartDashboard::PutString("Auto Turn Loop", "Done");
}*/

/*void DriveTrain::AutoTurnToAngle(float angle) {
	leftMaster.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	rightMaster.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	float p = (Constants::autoTurnMaxPwr - Constants::autoTurnMinPwr) * 100 / (Constants::autoTurnMaxAngle - Constants::autoTurnMinAngle);
	float error = CalculateAutoTurnError(angle);
	int errorMultiplier = 1; //1 or -1 to determine which way to turn
	if (error < 0) {
		error = -1 * error;
		errorMultiplier = -1; //might have to switch this to +1 and make errorMultiplier default to -1 depending on the way it turns, but this should be good. Let's test and see
	}
	int speed;
	int failsafe = 0;

	while (error > 3 && failsafe < 400) {
		if (error > Constants::autoTurnMaxAngle) {
			SmartDashboard::PutString("Auto Turn Loop", "Greater than max");
			error = CalculateAutoTurnError(angle);
			SmartDashboard::PutNumber("Auto Turn Error", error);
			speed = Constants::autoTurnMaxPwr * errorMultiplier;
			SmartDashboard::PutNumber("Auto Turn Speed", speed);
			TankDriveSpeed(speed, -1 * speed);
		} else if (error > Constants::autoTurnMinAngle && error < Constants::autoTurnMaxAngle) {
			SmartDashboard::PutString("Auto Turn Loop", "Between max and min");
			error = CalculateAutoTurnError(angle);
			SmartDashboard::PutNumber("Auto Turn Error", error);
			speed = p * ((error - Constants::autoTurnMinAngle) / 100) + Constants::autoTurnMinPwr * errorMultiplier;
			SmartDashboard::PutNumber("Auto Turn Speed", speed);
			TankDriveSpeed(speed, -1 * speed);
		} else if (error < Constants::autoTurnMinAngle && error > Constants::autoTurnMinDelta) {
			SmartDashboard::PutString("Auto Turn Loop", "Less than min");
			error = CalculateAutoTurnError(angle);
			SmartDashboard::PutNumber("Auto Turn Error", error);
			speed = Constants::autoTurnMinPwr * errorMultiplier;
			SmartDashboard::PutNumber("Auto Turn Speed", speed);
			TankDriveSpeed(speed, -1 * speed);
		}
		failsafe++;
		Wait(.001);
	}
}*/

void DriveTrain::AutoTurnToAngle(float angle) {
	int failsafe = 0;
	float error = CalculateAutoTurnError(angle);
	float motorOutput = 0;
	float minmotorpower = SmartDashboard::GetNumber("Min Motor Power", Constants::drivePIDMinSpeed);
	while (abs(error) > 3.0 && failsafe < 200) {
		if (abs(error) >= 90.0) {
			motorOutput = Constants::drivePIDMaxSpeed;
		} else if (abs(error) < 90.0 && abs(error) > 20.0) {
			motorOutput = ((Constants::drivePIDMaxSpeed - minmotorpower) * ((abs(error) - 20.0) / 70.0)) + minmotorpower;
		} else if (abs(error) <= 20.0) {
			motorOutput = minmotorpower;
		}
		if (error < 0)
			motorOutput *= -1;
		SmartDashboard::PutNumber("jj Motor Output", motorOutput);
		TankDriveSpeed(motorOutput, -motorOutput);
		Wait(.05);
		error = CalculateAutoTurnError(angle);
		SmartDashboard::PutNumber("jj Auto Turn Error:", error);
		SmartDashboard::PutNumber("jj Failsafe", failsafe);
		SmartDashboard::PutNumber("jj Angle", angle);
		std::cout << "Error: " << error << "\n";
		failsafe++;
	}  TankDriveSpeed(0.0, 0.0);
}

float DriveTrain::CalculateAutoTurnError(float angle) {
	float error;
	error = angle - position->GetAngleDegrees();
	SmartDashboard::PutNumber("jj Angle degrees", position->GetAngleDegrees());
	if (error > 180) {
		error -= 360;
	}
	else if (error < -180)
	{
		error += 360;
	}
	return error;
}
