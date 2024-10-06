#ifndef PUSHBUTTONS_H
#define PUSHBUTTONS_H

#include <Arduino.h>
#include <OneButton.h>

#define AMP_SWITCH_BUTTON_PIN 2
#define LOOP1_BUTTON_PIN 3
#define LOOP2_BUTTON_PIN 4
#define LOOP3_BUTTON_PIN 5
#define LOOP4_BUTTON_PIN 6

#define AMP_SWITCH_LED_PIN 7
#define LOOP1_LED_PIN 8
#define LOOP2_LED_PIN 9
#define LOOP3_LED_PIN 10
#define LOOP4_LED_PIN 11

class Pushbuttons
{
public:
	Pushbuttons()
		: ampSwitchButton(AMP_SWITCH_BUTTON_PIN, true),
		  loop1Button(LOOP1_BUTTON_PIN, true),
		  loop2Button(LOOP2_BUTTON_PIN, true),
		  loop3Button(LOOP3_BUTTON_PIN, true),
		  loop4Button(LOOP4_BUTTON_PIN, true)
	{
	}

private:
	OneButton ampSwitchButton;
	OneButton loop1Button;
	OneButton loop2Button;
	OneButton loop3Button;
	OneButton loop4Button;
};

#endif // PUSHBUTTONS_H