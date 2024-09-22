#include "AnalogPots.h"

#define BASS_PIN A0
#define MIDDLE_PIN A1
#define TREBLE_PIN A2
#define VOLUME_PIN A3

AnalogPots::AnalogPots() : bassPot(BASS_PIN, true), middlePot(MIDDLE_PIN, true), treblePot(TREBLE_PIN, true), volumePot(VOLUME_PIN, true)
{
}

AnalogPotValues AnalogPots::Read()
{
	return {
		bassPot.getValue(),
		middlePot.getValue(),
		treblePot.getValue(),
		volumePot.getValue()};
}

void AnalogPots::Tick()
{
	bassPot.update();
	middlePot.update();
	treblePot.update();
	volumePot.update();
}