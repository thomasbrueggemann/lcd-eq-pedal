#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

#include "Preset.h"

#define LCD_DIN 9
#define LCD_SCLK 8
#define LCD_A0 7
#define LCD_RESET 6
#define LCD_CS 5

#define CENTER 37
#define BAR_WIDTH 20

class LCD
{
public:
	LCD();

	void Begin();
	void Draw(Preset &preset, int bank);

private:
	ST7565_LCD display;

	void drawBar(int xPos, int potValue);
};

#endif // DISPLAY_H