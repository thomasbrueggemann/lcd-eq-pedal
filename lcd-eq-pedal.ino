#include <SPI.h>

#include "LCD.h"
#include "AnalogPots.h"
#include "Banks.h"
#include "Footswitches.h"

LCD lcd;
AnalogPots analogPots;
Banks banks;
Footswitches footswitches(banks);

void setup()
{
	Serial.begin(9600);
	lcd.Begin();
}

void loop()
{
	auto analogPotValues = analogPots.Read();
	lcd.Draw(analogPotValues, banks.GetCurrentBank());

	analogPots.Tick();
	footswitches.Tick();
}
