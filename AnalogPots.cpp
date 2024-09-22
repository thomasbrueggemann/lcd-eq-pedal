#include "AnalogPots.h"

#define BASS_PIN A0
#define MIDDLE_PIN A1
#define TREBLE_PIN A2
#define VOLUME_PIN A3

AnalogPotValues AnalogPots::Read()
{
	AnalogPotValues values;
	values.Bass = analogRead(BASS_PIN);
	values.Middle = analogRead(MIDDLE_PIN);
	values.Treble = analogRead(TREBLE_PIN);
	values.Volume = analogRead(VOLUME_PIN);

	return values;
}