#ifndef EDIT_TRACKER_H
#define EDIT_TRACKER_H

#include "Preset.h"
#include "AnalogPotValues.h"
#include "PushbuttonValues.h"

class EditTracker
{
public:
	EditTracker();

	void SetPreset(Preset &preset);
	Preset &GetPreset();
	Preset &TrackChanges(AnalogPotValues &analogPotValues, PushbuttonValues &pushbuttonValues);

private:
	Preset &currentPreset;
	AnalogPotValues &previousAnalogPotValues;
	PushbuttonValues &previousPushbuttonValues;
};

#endif // EDIT_TRACKER_H