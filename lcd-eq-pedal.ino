#include <SPI.h>

#include "LCD.h"
#include "AnalogPots.h"
#include "Banks.h"
#include "Footswitches.h"
#include "PresetStore.h"

LCD lcd;
AnalogPots analogPots;
Banks banks;
PresetStore presetStore;
Footswitches footswitches(banks, presetStore);

void setup()
{
	Serial.begin(9600);
	lcd.Begin();
}

void loop()
{
	auto analogPotValues = analogPots.Read();

	auto currentPreset = presetStore.GetCurrentPreset();
	if (currentPreset != nullptr)
	{
		auto presetAnalogPotValues = currentPreset.GetAnalogPotValues();
	}

	lcd.Draw(analogPotValues, banks.GetCurrentBank());

	analogPots.Tick();
	footswitches.Tick();
}
