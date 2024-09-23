#ifndef PRESETSTORE_H
#define PRESETSTORE_H

#include "Preset.h"
#include <Arduino.h>

#define NUM_PRESETS_PER_BANK 4
#define NUM_BYTES_PER_PRESET 12

#define BASS_ADDRESS 0
#define MIDDLE_ADDRESS 1
#define TREBLE_ADDRESS 2
#define VOLUME_ADDRESS 3
#define AMPSWITCH_ADDRESS 4
#define LOOP1_ADDRESS 5
#define LOOP2_ADDRESS 6

class PresetStore
{
public:
	PresetStore();

	void Write(int bank, int preset, Preset &payload);
	Preset Read(int bank, int preset);
	Preset GetCurrentPreset();

private:
	int getStartingAddress(int bank, int preset);
	Preset currentPreset;
};

#endif // PRESETSTORE_H