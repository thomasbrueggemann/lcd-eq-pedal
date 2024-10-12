#ifndef PUSHBUTTONS_H
#define PUSHBUTTONS_H

#include <Arduino.h>
#include <OneButton.h>

#define LOOP1_BUTTON_PIN 17
#define LOOP2_BUTTON_PIN 18
#define AMP_SWITCH_BUTTON_PIN 19
#define LOOP3_BUTTON_PIN 2
#define LOOP4_BUTTON_PIN 3

#define LOOP1_LED_PIN 21
#define LOOP2_LED_PIN 20
#define AMP_SWITCH_LED_PIN 14
#define LOOP3_LED_PIN 15
#define LOOP4_LED_PIN 16

class Pushbuttons
{
public:
	Pushbuttons();
	void Tick();
	PushbuttonValues Read();
	void ApplyPreset(Preset &preset);

private:
	OneButton ampSwitchButton;
	OneButton loop1Button;
	OneButton loop2Button;
	OneButton loop3Button;
	OneButton loop4Button;

	bool ampSwitchPressed = false;
	bool loop1Pressed = false;
	bool loop2Pressed = false;
	bool loop3Pressed = false;
	bool loop4Pressed = false;

	void handlePress(int buttonIndex);
	void toggleLeds();
};

#endif // PUSHBUTTONS_H