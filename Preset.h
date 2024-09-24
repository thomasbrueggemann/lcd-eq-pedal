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
		Serial.println("Bass: " + String(Bass));
		Serial.println("Middle: " + String(Middle));
		Serial.println("Treble: " + String(Treble));
		Serial.println("Volume: " + String(Volume));
		Serial.println("AmpSwitch: " + String(AmpSwitch ? "On" : "Off"));
		Serial.println("Loop1: " + String(Loop1 ? "On" : "Off"));
		Serial.println("Loop2: " + String(Loop2 ? "On" : "Off"));
	}
};

#endif // PRESET_H