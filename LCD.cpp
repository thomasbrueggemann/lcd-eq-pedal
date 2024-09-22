#include "LCD.h"

LCD::LCD(int8_t LCD_DIN, int8_t LCD_SCLK, int8_t LCD_A0, int8_t LCD_RESET, int8_t LCD_CS) 
  : display(LCD_DIN, LCD_SCLK, LCD_A0, LCD_RESET, LCD_CS)
{
}

void LCD::begin()
{
	display.begin(13);
}

void LCD::draw(AnalogPotValues &analogPotValues, int bank)
{
	display.clearDisplay();

	// legend
	display.setTextSize(1);
	display.setTextColor(ST7565_ON);
	display.setCursor(0, 0);
	display.println(F("Bass Mid Tre Vol Bank"));

	// bank number
	display.setTextSize(3);
	display.setTextColor(ST7565_ON);
	display.setCursor(105, CENTER - 10);
	display.println(F("1"));

	drawBar(0, analogPotValues.Bass);
	drawBar(25, analogPotValues.Middle);
	drawBar(50, analogPotValues.Treble);
	drawBar(75, analogPotValues.Volume);

	// axis
	display.drawLine(0, CENTER, 90, CENTER, ST7565_ON);

	display.display();
}

void LCD::drawBar(int xPos, int potValue)
{
	int height = map(potValue, 0, 1023, 25, -25);
	display.fillRect(xPos, CENTER, BAR_WIDTH, height, ST7565_INVERSE);
}