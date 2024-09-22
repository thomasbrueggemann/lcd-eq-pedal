#include "Banks.h"

Banks::Banks()
{
	currentBank = 0;
	SetPreset(0);
}

void Banks::SetPreset(byte preset)
{
	currentPreset = preset;

	Serial.print("Preset set to: ");
	Serial.println(currentPreset);
}

void Banks::BankUp()
{
	currentBank = (currentBank + 1) % MAX_BANKS;

	Serial.print("Bank up, new bank: ");
	Serial.println(currentBank);

	SetPreset(0);
}

void Banks::BankDown()
{
	currentBank = (currentBank - 1 + MAX_BANKS) % MAX_BANKS;

	Serial.print("Bank down, new bank: ");
	Serial.println(currentBank);

	SetPreset(0);
}

byte Banks::GetCurrentBank()
{
	return currentBank;
}

byte Banks::GetCurrentPreset()
{
	return currentPreset;
}