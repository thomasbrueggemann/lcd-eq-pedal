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
	if (preset.AmpSwitch != ampSwitchPressed)
	{
		ampSwitchPressed = preset.AmpSwitch;
		digitalWrite(AMP_SWITCH_LED_PIN, ampSwitchPressed ? LOW : HIGH);
		delay(LED_TOGGLE_DELAY);
	}

	if (preset.Loop1 != loop1Pressed)
	{
		loop1Pressed = preset.Loop1;
		digitalWrite(LOOP1_LED_PIN, loop1Pressed ? HIGH : LOW);
		delay(LED_TOGGLE_DELAY);
	}

	if (preset.Loop2 != loop2Pressed)
	{
		loop2Pressed = preset.Loop2;
		digitalWrite(LOOP2_LED_PIN, loop2Pressed ? HIGH : LOW);
		delay(LED_TOGGLE_DELAY);
	}

	if (preset.Loop3 != loop3Pressed)
	{
		loop3Pressed = preset.Loop3;
		digitalWrite(LOOP3_LED_PIN, loop3Pressed ? HIGH : LOW);
		delay(LED_TOGGLE_DELAY);
	}

	if (preset.Loop4 != loop4Pressed)
	{
		loop4Pressed = preset.Loop4;
		digitalWrite(LOOP4_LED_PIN, loop4Pressed ? HIGH : LOW);
		delay(LED_TOGGLE_DELAY);
	}
}

void Pushbuttons::HandlePress(int pin)
{
	switch (pin)
	{
	case AMP_SWITCH_BUTTON_PIN:
		if (ampSwitchPressed == true)
		{
			ampSwitchPressed = false;
		}
		else
		{
			ampSwitchPressed = true;
		}

		digitalWrite(AMP_SWITCH_LED_PIN, ampSwitchPressed ? LOW : HIGH);
		break;
	case LOOP1_BUTTON_PIN:
		if (loop1Pressed == true)
		{
			loop1Pressed = false;
		}
		else
		{
			loop1Pressed = true;
		}
		digitalWrite(LOOP1_LED_PIN, loop1Pressed ? HIGH : LOW);
		break;
	case LOOP2_BUTTON_PIN:
		if (loop2Pressed == true)
		{
			loop2Pressed = false;
		}
		else
		{
			loop2Pressed = true;
		}
		digitalWrite(LOOP2_LED_PIN, loop2Pressed ? HIGH : LOW);
		break;
	case LOOP3_BUTTON_PIN:
		if (loop3Pressed == true)
		{
			loop3Pressed = false;
		}
		else
		{
			loop3Pressed = true;
		}
		digitalWrite(LOOP3_LED_PIN, loop3Pressed ? HIGH : LOW);
		break;
	case LOOP4_BUTTON_PIN:
		if (loop4Pressed == true)
		{
			loop4Pressed = false;
		}
		else
		{
			loop4Pressed = true;
		}
		digitalWrite(LOOP4_LED_PIN, loop4Pressed ? HIGH : LOW);
		break;
	}
}
