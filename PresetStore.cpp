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

	EEPROM.update(startingAddress + BASS_ADDRESS, payload.Bass);
	EEPROM.update(startingAddress + MIDDLE_ADDRESS, payload.Middle);
	EEPROM.update(startingAddress + TREBLE_ADDRESS, payload.Treble);
	EEPROM.update(startingAddress + VOLUME_ADDRESS, payload.Volume);
	EEPROM.update(startingAddress + AMPSWITCH_ADDRESS, payload.AmpSwitch);
	EEPROM.update(startingAddress + LOOP1_ADDRESS, payload.Loop1);
	EEPROM.update(startingAddress + LOOP2_ADDRESS, payload.Loop2);
	EEPROM.update(startingAddress + LOOP3_ADDRESS, payload.Loop3);
	EEPROM.update(startingAddress + LOOP4_ADDRESS, payload.Loop4);
}

Preset PresetStore::Read(int bank, int preset)
{
	Preset p;

	int startingAddress = getStartingAddress(bank, preset);
	EEPROM.get(startingAddress + BASS_ADDRESS, p.Bass);
	EEPROM.get(startingAddress + MIDDLE_ADDRESS, p.Middle);
	EEPROM.get(startingAddress + TREBLE_ADDRESS, p.Treble);
	EEPROM.get(startingAddress + VOLUME_ADDRESS, p.Volume);
	EEPROM.get(startingAddress + AMPSWITCH_ADDRESS, p.AmpSwitch);
	EEPROM.get(startingAddress + LOOP1_ADDRESS, p.Loop1);
	EEPROM.get(startingAddress + LOOP2_ADDRESS, p.Loop2);
	EEPROM.get(startingAddress + LOOP3_ADDRESS, p.Loop3);
	EEPROM.get(startingAddress + LOOP4_ADDRESS, p.Loop4);

	return p;
}

int PresetStore::getStartingAddress(int bank, int preset)
{
	int startingAddress = (bank * NUM_PRESETS_PER_BANK + preset) * NUM_BYTES_PER_PRESET;
	return startingAddress;
}