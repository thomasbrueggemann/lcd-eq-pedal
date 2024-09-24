#include "EditTracker.h"

EditTracker::EditTracker()
{
	currentPreset = Preset{0, 0, 0, 0, false, false, false};
	previousAnalogPotValues = AnalogPotValues{0, 0, 0, 0};
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
