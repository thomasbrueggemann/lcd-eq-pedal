#include "Pushbuttons.h"

Pushbuttons::Pushbuttons()
{
	pinMode(AMP_SWITCH_LED_PIN, OUTPUT);
	pinMode(LOOP1_LED_PIN, OUTPUT);
	pinMode(LOOP2_LED_PIN, OUTPUT);
	pinMode(LOOP3_LED_PIN, OUTPUT);
	pinMode(LOOP4_LED_PIN, OUTPUT);
}

PushbuttonValues Pushbuttons::Read()
{
	PushbuttonValues values;
	values.AmpSwitch = ampSwitchPressed;
	values.Loop1 = loop1Pressed;
	values.Loop2 = loop2Pressed;
	values.Loop3 = loop3Pressed;
	values.Loop4 = loop4Pressed;
	return values;
}

void Pushbuttons::ApplyPreset(Preset &preset)
{
	ampSwitchPressed = preset.AmpSwitch;
	loop1Pressed = preset.Loop1;
	loop2Pressed = preset.Loop2;
	loop3Pressed = preset.Loop3;
	loop4Pressed = preset.Loop4;

	toggleLeds();
}

void Pushbuttons::HandlePress(int pin)
{
  Serial.println("Button pin pressed:");
  Serial.println(pin);

	switch (pin)
	{
	case AMP_SWITCH_BUTTON_PIN:
		ampSwitchPressed = !ampSwitchPressed;
		break;
	case LOOP1_BUTTON_PIN:
		loop1Pressed = !loop1Pressed;
		break;
	case LOOP2_BUTTON_PIN:
		loop2Pressed = !loop2Pressed;
		break;
	case LOOP3_BUTTON_PIN:
		loop3Pressed = !loop3Pressed;
		break;
	case LOOP4_BUTTON_PIN:
		loop4Pressed = !loop4Pressed;
		break;
	}

	toggleLeds();
}

void Pushbuttons::toggleLeds()
{
	digitalWrite(AMP_SWITCH_LED_PIN, ampSwitchPressed ? HIGH : LOW);
	digitalWrite(LOOP1_LED_PIN, loop1Pressed ? HIGH : LOW);
	digitalWrite(LOOP2_LED_PIN, loop2Pressed ? HIGH : LOW);
	digitalWrite(LOOP3_LED_PIN, loop3Pressed ? HIGH : LOW);
	digitalWrite(LOOP4_LED_PIN, loop4Pressed ? HIGH : LOW);
}