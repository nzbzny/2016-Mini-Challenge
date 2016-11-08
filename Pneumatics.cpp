#include "Pneumatics.h"

Pneumatics::Pneumatics (UINT32 InSoleChannel, UINT32 OutSoleChannel):
  InSole (InSoleChannel),
  OutSole (OutSoleChannel)
{    }

void Pneumatic::Set (bool state)
{
  if (InSole.Get())
  {
    InSole.Set (!state);
    OutSole.Set (state);
  }
  else
  {
    OutSole.Set (state);
    InSole.Set (!state);
  }
}

void Pneumatic::Get ()
{
  return OutSole.Get();
}
