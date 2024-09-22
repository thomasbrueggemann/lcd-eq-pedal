#ifndef BANKS_H
#define BANKS_H

#include <Arduino.h>

#include "SegmentDisplay.h"
#include "LED.h"

#define MAX_BANKS 10
#define MAX_PRESETS 4

class Banks
{
public:
	Banks(LED &led, SegmentDisplay &segmentDisplay);

	void SetPreset(byte preset);
	void BankUp();
	void BankDown();

	byte GetCurrentBank();
	byte GetCurrentPreset();

private:
	byte currentBank;
	byte currentPreset;

	SegmentDisplay &segmentDisplay;
	LED &led;

	void updateDisplay();
};

#endif