#ifndef BANKS_H
#define BANKS_H

#include <Arduino.h>

#define MAX_BANKS 10
#define MAX_PRESETS 3

class Banks
{
public:
	Banks();

	void SetPreset(int preset);
	void BankUp();
	void BankDown();

	int GetCurrentBank();
	int GetCurrentPreset();

private:
	int currentBank;
	int currentPreset;
};

#endif