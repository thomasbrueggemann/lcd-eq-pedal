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
	Preset Read(int preset);
	void PreloadBank(int bank);

private:
	int getStartingAddress(int bank, int preset);

	Preset BankPresets[6];

};

#endif // PRESETSTORE_H