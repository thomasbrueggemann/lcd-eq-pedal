#include "Banks.h"

Banks::Banks()
{
	currentBank = 5;
	SetPreset(3);
}

void Banks::SetPreset(int preset)
{
	currentPreset = preset;

	Serial.print("Preset set to: ");
	Serial.println(currentPreset);
}

void Banks::BankUp()
{
	currentBank++;

	Serial.print("Bank up, new bank: ");
	Serial.println(currentBank);

	SetPreset(0);
}

void Banks::BankDown()
{
	currentBank--;

	Serial.print("Bank down, new bank: ");
	Serial.println(currentBank);

	SetPreset(0);
}

int Banks::GetCurrentBank()
{
	return currentBank;
}

int Banks::GetCurrentPreset()
{
	return currentPreset;
}