#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

#define CENTER 37
#define BAR_WIDTH 20

class LCD
{
public:
	LCD(int LCD_DIN, int LCD_SCLK, int LCD_A0, int LCD_RESET, int LCD_CS);

	void begin();
	void draw(AnalogPotValues &analogPotValues, int bank);

private:
	ST7565_LCD display;
};

#endif // DISPLAY_H