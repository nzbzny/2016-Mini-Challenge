#include "Pneumatics.h"

Pneumatics::Pneumatics (UINT32 InSoleChannel, UINT32 OutSoleChannel):
  InSole (InSoleChannel),
  OutSole (OutSoleChannel)
{    }

void Pneumatic::Set (bool state)
{
  pneumaticController.Set(state+1);
}

bool Pneumatic::Get ()
{
  return pneumaticController.Get() - 1;
}
