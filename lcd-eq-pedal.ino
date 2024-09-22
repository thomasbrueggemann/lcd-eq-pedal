#include <SPI.h>

#include "LCD.h"
#include "AnalogPots.h"

#define LCD_DIN 9
#define LCD_SCLK 8
#define LCD_A0 7
#define LCD_RESET 6
#define LCD_CS 5

LCD display(LCD_DIN, LCD_SCLK, LCD_A0, LCD_RESET, LCD_CS);
AnalogPots analogPots;

void setup()
{
	Serial.begin(9600);
	display.begin();
}

void loop()
{
	auto analogPotValues = analogPots.Read();
	display.draw(analogPotValues, 1);

	delay(10);
}
