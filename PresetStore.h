#ifndef PRESETSTORE_H
#define PRESETSTORE_H

#include <Arduino.h>

#include "Preset.h"

#define NUM_PRESETS_PER_BANK 6
#define NUM_BYTES_PER_PRESET 16

class PresetStore
{
public:
	void Write(int bank, int preset, Preset &payload);
	Preset Read(int preset);
	void PreloadBank(int bank);
	void DebugDump();

private:
	int getStartingAddress(int bank, int preset);
	bool isValidAddress(int address, int size);
	bool isValidBankPreset(int bank, int preset);

	Preset BankPresets[6];
	int currentBank;
};

#endif // PRESETSTORE_H