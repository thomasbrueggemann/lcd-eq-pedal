#include <SPI.h>

#include "LCD.h"
#include "AnalogPots.h"
#include "Banks.h"
#include "Footswitches.h"
#include "PresetStore.h"
#include "EditTracker.h"

LCD lcd;
AnalogPots analogPots;
Banks banks;
EditTracker editTracker;
PresetStore presetStore(editTracker);
Footswitches footswitches(banks, presetStore);

void setup()
{
	Serial.begin(9600);
	lcd.Begin();
}

void loop()
{
	auto analogPotValues = analogPots.Read();
	auto preset = editTracker.TrackChanges(analogPotValues);

	lcd.Draw(preset, banks.GetCurrentBank());

	analogPots.Tick();
	footswitches.Tick();
}
