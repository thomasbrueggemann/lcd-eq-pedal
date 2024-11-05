#include "PresetStore.h"
#include <EEPROM.h>

/*

EEPROM address format
----------------------
0 = bass, preset 0, bank 0
1 = mid
2 = treble
3 = boost
4 = ampswitch
5 = loop 1
6 = loop 2
7 = loop 3
8 = loop 4
9 reserved
10 = cut, preset 1, bank 0
11 = ...

*/

void PresetStore::Write(int bank, int preset, Preset &payload)
{
	int startingAddress = getStartingAddress(bank, preset);

	EEPROM.put(startingAddress, payload);
	BankPresets[preset] = payload;
}

Preset PresetStore::Read(int preset)
{
	return BankPresets[preset];
}

void PresetStore::PreloadBank(int bank)
{
	for(int i = 0; i < NUM_PRESETS_PER_BANK; i++)
	{
		int startingAddress = getStartingAddress(bank, i);
		EEPROM.get(startingAddress, BankPresets[i]);
	}
}

int PresetStore::getStartingAddress(int bank, int preset)
{
	int startingAddress = (bank * NUM_PRESETS_PER_BANK + preset) * NUM_BYTES_PER_PRESET;
	return startingAddress;
}