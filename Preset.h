#ifndef PRESET_H
#define PRESET_H

#include <Arduino.h>

#include "AnalogPotValues.h"
#include "Debug.h"

class Preset
{
public:
	int Bass;
	int Middle;
	int Treble;
	int Volume;
	bool AmpSwitch;
	bool Loop1;
	bool Loop2;
	bool Loop3;
	bool Loop4;

	bool PresetChanged;

	Preset() {}

	Preset(AnalogPotValues &values)
	{
		Bass = values.Bass;
		Middle = values.Middle;
		Treble = values.Treble;
		Volume = values.Volume;
	}

	AnalogPotValues GetAnalogPotValues()
	{
		return {Bass, Middle, Treble, Volume};
	}

	void Print()
	{
		D_print("Bass: " + String(Bass));
		D_print(", Middle: " + String(Middle));
		D_print(", Treble: " + String(Treble));
		D_println(", Volume: " + String(Volume));
		D_print("AmpSwitch: " + String(AmpSwitch ? "On" : "Off"));
		D_print(", Loop1: " + String(Loop1 ? "On" : "Off"));
		D_print(", Loop2: " + String(Loop2 ? "On" : "Off"));
		D_print(", Loop3: " + String(Loop3 ? "On" : "Off"));
		D_println(", Loop4: " + String(Loop4 ? "On" : "Off"));
	}
};

#endif // PRESET_H