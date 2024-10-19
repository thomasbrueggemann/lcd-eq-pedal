#include "LCD.h"

LCD::LCD()
	: display(LCD_PIN_DIN, LCD_PIN_SCLK, LCD_PIN_A0, LCD_PIN_RESET, LCD_PIN_CS)
{
}

void LCD::Begin()
{
	display.begin(13);
  display.setRotation(2);
}

void LCD::Draw(Preset &preset, int bank)
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
	display.println(bank);

	drawBar(0, preset.Bass);
	drawBar(25, preset.Middle);
	drawBar(50, preset.Treble);
	drawBar(75, preset.Volume);

	// axis
	display.drawLine(0, CENTER, 90, CENTER, ST7565_ON);

	display.display();
}

void LCD::drawBar(int xPos, int potValue)
{
	int height = map(potValue, 0, 1023, 25, -25);
	display.fillRect(xPos, CENTER, BAR_WIDTH, height, ST7565_INVERSE);
}