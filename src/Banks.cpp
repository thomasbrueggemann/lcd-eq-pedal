#include "Banks.h"

Banks::Banks(LED &led, SegmentDisplay &segmentDisplay) : segmentDisplay(segmentDisplay), led(led)
{
	currentBank = 0;
	SetPreset(0);

	updateDisplay();
}

void Banks::SetPreset(byte preset)
{
	currentPreset = preset;
	led.SwitchTo(currentPreset);

	Serial.print("Preset set to: ");
	Serial.println(currentPreset);
}

void Banks::BankUp()
{
	currentBank = (currentBank + 1) % MAX_BANKS;

	Serial.print("Bank up, new bank: ");
	Serial.println(currentBank);

	SetPreset(0);
	updateDisplay();
}

void Banks::BankDown()
{
	currentBank = (currentBank - 1 + MAX_BANKS) % MAX_BANKS;

	Serial.print("Bank down, new bank: ");
	Serial.println(currentBank);

	SetPreset(0);
	updateDisplay();
}

byte Banks::GetCurrentBank()
{
	return currentBank;
}

byte Banks::GetCurrentPreset()
{
	return currentPreset;
}

void Banks::updateDisplay()
{
	segmentDisplay.DisplayNumber(currentBank + 1);
}