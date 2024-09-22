#ifndef BANKS_H
#define BANKS_H

#include <Arduino.h>

#define MAX_BANKS 10
#define MAX_PRESETS 4

class Banks
{
public:
	Banks();

	void SetPreset(byte preset);
	void BankUp();
	void BankDown();

	byte GetCurrentBank();
	byte GetCurrentPreset();

private:
	byte currentBank;
	byte currentPreset;
};

#endif