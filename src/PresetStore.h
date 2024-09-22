#ifndef PRESETSTORE_H
#define PRESETSTORE_H

#include "Preset.h"
#include <Arduino.h>

#define NUM_PRESETS_PER_BANK 4
#define NUM_BYTES_PER_PRESET 12

#define CUT_ADDRESS 0
#define BASS_ADDRESS 1
#define MIDDLE_ADDRESS 2
#define TREBLE_ADDRESS 3
#define BOOST_ADDRESS 4
#define AMPSWITCH_ADDRESS 5

class PresetStore
{
public:
	PresetStore();

	void WritePreset(byte bank, byte preset, Preset &payload);
	Preset ReadPreset(byte bank, byte preset);

private:
	int getStartingAddress(byte bank, byte preset);
};

#endif // PRESETSTORE_H