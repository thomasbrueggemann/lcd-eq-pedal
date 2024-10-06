#include "EditTracker.h"

EditTracker::EditTracker()
{
	currentPreset = Preset();
	previousAnalogPotValues = AnalogPotValues();
}

void EditTracker::SetPreset(Preset &preset)
{
	currentPreset = preset;
}

Preset &EditTracker::GetPreset()
{
	return currentPreset;
}

Preset &EditTracker::TrackChanges(AnalogPotValues &analogPotValues)
{
	if (analogPotValues.Bass != previousAnalogPotValues.Bass)
	{
		currentPreset.Bass = analogPotValues.Bass;
	}

	if (analogPotValues.Middle != previousAnalogPotValues.Middle)
	{
		currentPreset.Middle = analogPotValues.Middle;
	}

	if (analogPotValues.Treble != previousAnalogPotValues.Treble)
	{
		currentPreset.Treble = analogPotValues.Treble;
	}

	if (analogPotValues.Volume != previousAnalogPotValues.Volume)
	{
		currentPreset.Volume = analogPotValues.Volume;
	}

	previousAnalogPotValues = analogPotValues;

	return currentPreset;
}
