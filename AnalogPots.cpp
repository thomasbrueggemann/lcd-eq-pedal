#include "AnalogPots.h"

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