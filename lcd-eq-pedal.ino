#include <SPI.h>

#include "LCD.h"
#include "AnalogPots.h"
#include "Banks.h"
#include "Footswitches.h"
#include "PresetStore.h"
#include "EditTracker.h"
#include "Relays.h"
#include "Vactrols.h"

LCD lcd;
Relays relays;
Vactrols vactrols;
AnalogPots analogPots;
Banks banks;
EditTracker editTracker;
PresetStore presetStore;
Footswitches footswitches(banks, presetStore, editTracker);

void setup()
{
	Serial.begin(9600);
  SPI.begin();
	lcd.Begin();

	vactrols.SetBass(512);
}

void loop()
{
	/*
	auto analogPotValues = analogPots.Read();
	auto preset = editTracker.TrackChanges(analogPotValues);

	relays.Toggle(preset);
	lcd.Draw(preset, banks.GetCurrentBank());
	vactrols.ApplyPreset(preset);

	analogPots.Tick();
	footswitches.Tick();
	*/


	vactrols.SetBass(512);
  delay(2000);
}
