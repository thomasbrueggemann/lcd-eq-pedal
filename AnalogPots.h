#ifndef ANALOGPOTS_H
#define ANALOGPOTS_H

#include <Arduino.h>
#include <ResponsiveAnalogRead.h>

#include "AnalogPotValues.h"

#define BASS_PIN A0
#define MIDDLE_PIN A1
#define TREBLE_PIN A2
#define VOLUME_PIN A3

class AnalogPots
{
public:
	AnalogPots();

	AnalogPotValues Read();
	void Tick();

private:
	ResponsiveAnalogRead bassPot;
	ResponsiveAnalogRead middlePot;
	ResponsiveAnalogRead treblePot;
	ResponsiveAnalogRead volumePot;
};

#endif // ANALOGPOTS_H