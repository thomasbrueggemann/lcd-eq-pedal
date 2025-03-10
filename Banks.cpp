#include "Banks.h"

Banks::Banks()
{
	currentBank = 0;
	SetPreset(0);
}

void Banks::SetPreset(int preset)
{
	currentPreset = preset;
}

void Banks::BankUp()
{
	currentBank++;
	
	if (currentBank > MAX_BANKS) {
		currentBank = 0;
	}

	SetPreset(0);
}

void Banks::BankDown()
{
	currentBank--;

	if (currentBank < 0) {
		currentBank = MAX_BANKS;
	}

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