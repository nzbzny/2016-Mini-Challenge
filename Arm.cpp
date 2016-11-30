#include "Arm.h"

Arm::Arm() {
  gripper(Constants::gripperInSole, Constants::gripperOutSole),
  motor(Constants::armChannel),
  upperSwitch(Constants::armUpperLimitChannel),
  lowerSwitch(Constants::armLowerLimitChannel)
}


void Arm::raise() {
  motor.Set(.5);
  if (upperSwitch.Get()) {
      motor.Set(0);
  }
}

void Arm::lower() {
  motor.Set(-.5);
  if (lowerSwitch.Get()) {
    motor.Set(0);
  }
}

void Arm::stop() {
  motor.Set(0);
}

void Arm::gripOpen() {
  gripper.Set(true);
}

void Arm::gripClose() {
  gripper.Set(false);
}
