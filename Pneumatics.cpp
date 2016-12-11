#include "Pneumatics.h"

Pneumatics::Pneumatics(UINT32 InSoleChannel, UINT32 OutSoleChannel):
	InSole (InSoleChannel),
	OutSole (OutSoleChannel)
{    }

void Pneumatics::set (bool state)
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

bool Pneumatics::get ()
{
		return OutSole.Get();
}
