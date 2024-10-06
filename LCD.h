#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

#include "Preset.h"

#define LCD_PIN_DIN 40
#define LCD_PIN_SCLK 39
#define LCD_PIN_A0 38
#define LCD_PIN_RESET 37
#define LCD_PIN_CS 36

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