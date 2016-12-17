#include "Arm.h"

Arm::Arm() :
  gripper(Constants::gripperInSole, Constants::gripperOutSole),
  motor(Constants::armChannel),
  upperSwitch(Constants::armUpperLimitChannel),
  lowerSwitch(Constants::armLowerLimitChannel)
{}


void Arm::move(int speed) {
  if (upperSwitch.Get() || lowerSwitch.Get()) {
    arm.Set(0);
    return;
  }
  arm.Set(speed);
}

void Arm::grip(bool state) {
  gripper.set(state);
}

bool Arm::getGrip() {
  return gripper.get();
}
