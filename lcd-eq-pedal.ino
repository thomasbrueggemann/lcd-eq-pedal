#include <Arduino.h>
#include <SPI.h>

#include "LCD.h"
#include "AnalogPots.h"
#include "Banks.h"
#include "Footswitches.h"
#include "PresetStore.h"
#include "EditTracker.h"
#include "Relays.h"
#include "Vactrols.h"
#include "Pushbuttons.h"

LCD lcd;
Relays relays;
Vactrols vactrols;
AnalogPots analogPots;
Banks banks;
EditTracker editTracker;
PresetStore presetStore;
Footswitches footswitches(banks, presetStore, editTracker);
Pushbuttons pushbuttons;

void setup()
{
	Serial.begin(9600);
	Serial.println("*** LCD EQ PEDAL ***");

	SPI.begin();
	lcd.Begin();

	vactrols.SetBass(10);
}

void loop()
{
	auto analogPotValues = analogPots.Read();
	auto pushbuttonValues = pushbuttons.Read();

	auto preset = editTracker.TrackChanges(analogPotValues, pushbuttonValues);

	relays.Toggle(preset);
	lcd.Draw(preset, banks.GetCurrentBank());
	vactrols.ApplyPreset(preset);

	analogPots.Tick();
	footswitches.Tick();
	pushbuttons.Tick();
}
