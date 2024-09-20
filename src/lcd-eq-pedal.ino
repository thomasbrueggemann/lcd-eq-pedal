#include <SPI.h>
#include <Adafruit_GFX.h>
#include <ST7565_LCD.h>

#define LCD_DIN 9
#define LCD_SCLK 8
#define LCD_A0 7
#define LCD_RESET 6
#define LCD_CS 5

#define CENTER 37
#define BAR_WIDTH 20

ST7565_LCD display = ST7565_LCD(LCD_DIN, LCD_SCLK, LCD_A0, LCD_RESET, LCD_CS);

void setup()
{
	Serial.begin(9600);

	// initialize the ST7565 LCD display with contrast = 13 (0 <= coontrast <= 63)
	display.begin(13);
}

// main loop (nothing here!)
void loop()
{
	int bassPot = analogRead(A0);
	int midPot = analogRead(A1);
	int treblePot = analogRead(A2);
	int volumePot = analogRead(A3);

	draw(bassPot, midPot, treblePot, volumePot);

	delay(10);
}

void draw(int bassPot, int midPot, int treblePot, int volumePot)
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

	drawBar(0, bassPot);
	drawBar(25, midPot);
	drawBar(50, treblePot);
	drawBar(75, volumePot);

	// axis
	display.drawLine(0, CENTER, 90, CENTER, ST7565_ON);

	display.display();
}

void drawBar(int xPos, int potValue)
{
	int height = map(potValue, 0, 1023, 25, -25);
	display.fillRect(xPos, CENTER, BAR_WIDTH, height, ST7565_INVERSE);
}