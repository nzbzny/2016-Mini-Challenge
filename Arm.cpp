#include "Arm.h"

Arm::Arm() :
  gripper(Constants::gripperInSole, Constants::gripperOutSole),
  motor(Constants::armChannel),
  upperSwitch(Constants::armUpperLimitChannel),
  lowerSwitch(Constants::armLowerLimitChannel)
{}


void Arm::raise() {
  motor.Set(.25);
  if (upperSwitch.Get()) {
      motor.Set(0);
  }
}

void Arm::lower() {
  motor.Set(-.25);
  if (lowerSwitch.Get()) {
    motor.Set(0);
  }
}

void Arm::stop() {
  motor.Set(0);
}

void Arm::grip(bool state) {
  gripper.set(state);
}

bool Arm::getGrip() {
  return gripper.get();
}
