#ifndef PRESETSTORE_H
#define PRESETSTORE_H

#include <Arduino.h>

#include "Preset.h"

#define NUM_PRESETS_PER_BANK 6
#define NUM_BYTES_PER_PRESET 50

class PresetStore
{
public:
	void Write(int bank, int preset, Preset &payload);
	Preset Read(int bank, int preset);

private:
	int getStartingAddress(int bank, int preset);
};

#endif // PRESETSTORE_H