#ifndef PRESET_H
#define PRESET_H

#include <Arduino.h>
#include "AnalogPotValues.h"

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
		Serial.print("Bass: " + String(Bass));
		Serial.print(", Middle: " + String(Middle));
		Serial.print(", Treble: " + String(Treble));
		Serial.println(", Volume: " + String(Volume));
		Serial.print("AmpSwitch: " + String(AmpSwitch ? "On" : "Off"));
		Serial.print(", Loop1: " + String(Loop1 ? "On" : "Off"));
		Serial.print(", Loop2: " + String(Loop2 ? "On" : "Off"));
		Serial.print(", Loop3: " + String(Loop3 ? "On" : "Off"));
		Serial.println(", Loop4: " + String(Loop4 ? "On" : "Off"));
	}
};

#endif // PRESET_H