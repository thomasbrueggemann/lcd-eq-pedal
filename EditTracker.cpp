#include "EditTracker.h"

void EditTracker::SetPreset(Preset &preset)
{
	currentPreset = preset;
}

Preset &EditTracker::GetPreset()
{
	return currentPreset;
}

Preset &EditTracker::TrackChanges(AnalogPotValues &analogPotValues, PushbuttonValues &pushbuttonValues)
{
	currentPreset.PresetChanged = false;

	if (analogPotValues.Bass != previousAnalogPotValues.Bass)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Bass = analogPotValues.Bass;
	}

	if (analogPotValues.Middle != previousAnalogPotValues.Middle)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Middle = analogPotValues.Middle;
	}

	if (analogPotValues.Treble != previousAnalogPotValues.Treble)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Treble = analogPotValues.Treble;
	}

	if (analogPotValues.Volume != previousAnalogPotValues.Volume)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Volume = analogPotValues.Volume;
	}

	previousAnalogPotValues = analogPotValues;

	if (pushbuttonValues.AmpSwitch != previousPushbuttonValues.AmpSwitch)
	{
		currentPreset.PresetChanged = true;
		currentPreset.AmpSwitch = pushbuttonValues.AmpSwitch;
	}

	if (pushbuttonValues.Loop1 != previousPushbuttonValues.Loop1)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Loop1 = pushbuttonValues.Loop1;
	}

	if (pushbuttonValues.Loop2 != previousPushbuttonValues.Loop2)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Loop2 = pushbuttonValues.Loop2;
	}

	if (pushbuttonValues.Loop3 != previousPushbuttonValues.Loop3)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Loop3 = pushbuttonValues.Loop3;
	}

	if (pushbuttonValues.Loop4 != previousPushbuttonValues.Loop4)
	{
		currentPreset.PresetChanged = true;
		currentPreset.Loop4 = pushbuttonValues.Loop4;
	}

	previousPushbuttonValues = pushbuttonValues;

	return currentPreset;
}