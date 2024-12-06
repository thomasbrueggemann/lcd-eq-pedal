#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

#include "Preset.h"

#define LCD_PIN_DIN 29
#define LCD_PIN_SCLK 31
#define LCD_PIN_A0 30
#define LCD_PIN_RESET 28
#define LCD_PIN_CS 26

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