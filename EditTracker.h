#ifndef EDIT_TRACKER_H
#define EDIT_TRACKER_H

#include "Preset.h"
#include "AnalogPotValues.h"

class EditTracker
{
public:
	EditTracker();

	void SetPreset(Preset &preset);
	Preset &GetPreset();
	Preset &TrackChanges(AnalogPotValues &analogPotValues);

private:
	Preset &currentPreset;
	AnalogPotValues &previousAnalogPotValues;
};

#endif // EDIT_TRACKER_H