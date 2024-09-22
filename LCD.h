#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

#include "AnalogPotValues.h"

#define CENTER 37
#define BAR_WIDTH 20

class LCD
{
public:
	LCD(int8_t LCD_DIN, int8_t LCD_SCLK, int8_t LCD_A0, int8_t LCD_RESET, int8_t LCD_CS);

	void begin();
	void draw(AnalogPotValues &analogPotValues, int bank);

private:
	ST7565_LCD display;

  void drawBar(int xPos, int potValue);
};

#endif // DISPLAY_H