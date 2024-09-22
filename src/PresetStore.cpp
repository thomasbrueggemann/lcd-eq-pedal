#include "PresetStore.h"

#include <EEPROM.h>

/*

EEPROM address format
----------------------
0 = cut, preset 0, bank 0
1 = bass
2 = mid
3 = treble
4 = boost
5 = ampswitch
6 reserved
7 reserved
8 reserved
9 reserved
10 = cut, preset 1, bank 0
11 = ...

*/

PresetStore::PresetStore()
{
}

void PresetStore::WritePreset(byte bank, byte preset, Preset &payload)
{
	int startingAddress = getStartingAddress(bank, preset);

	EEPROM.update(startingAddress + CUT_ADDRESS, payload.Cut);
	EEPROM.update(startingAddress + BASS_ADDRESS, payload.Bass);
	EEPROM.update(startingAddress + MIDDLE_ADDRESS, payload.Middle);
	EEPROM.update(startingAddress + TREBLE_ADDRESS, payload.Treble);
	EEPROM.update(startingAddress + BOOST_ADDRESS, payload.Boost);
	EEPROM.update(startingAddress + AMPSWITCH_ADDRESS, payload.AmpSwitch);
}

Preset PresetStore::ReadPreset(byte bank, byte preset)
{
	Preset p;

	int startingAddress = getStartingAddress(bank, preset);
	EEPROM.get(startingAddress + CUT_ADDRESS, p.Cut);
	EEPROM.get(startingAddress + BASS_ADDRESS, p.Bass);
	EEPROM.get(startingAddress + MIDDLE_ADDRESS, p.Middle);
	EEPROM.get(startingAddress + TREBLE_ADDRESS, p.Treble);
	EEPROM.get(startingAddress + BOOST_ADDRESS, p.Boost);
	EEPROM.get(startingAddress + AMPSWITCH_ADDRESS, p.AmpSwitch);

	return p;
}

int PresetStore::getStartingAddress(byte bank, byte preset)
{
	int startingAddress = (bank * NUM_PRESETS_PER_BANK + preset) * NUM_BYTES_PER_PRESET;
	return startingAddress;
}