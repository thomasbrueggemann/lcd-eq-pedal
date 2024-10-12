#include "Pushbuttons.h"

Pushbuttons::Pushbuttons()
	: ampSwitchButton(AMP_SWITCH_BUTTON_PIN, true),
	  loop1Button(LOOP1_BUTTON_PIN, true),
	  loop2Button(LOOP2_BUTTON_PIN, true),
	  loop3Button(LOOP3_BUTTON_PIN, true),
	  loop4Button(LOOP4_BUTTON_PIN, true)
{
	pinMode(AMP_SWITCH_BUTTON_PIN, OUTPUT);
	pinMode(LOOP1_BUTTON_PIN, OUTPUT);
	pinMode(LOOP2_BUTTON_PIN, OUTPUT);
	pinMode(LOOP3_BUTTON_PIN, OUTPUT);
	pinMode(LOOP4_BUTTON_PIN, OUTPUT);

	pinMode(AMP_SWITCH_LED_PIN, OUTPUT);
	pinMode(LOOP1_LED_PIN, OUTPUT);
	pinMode(LOOP2_LED_PIN, OUTPUT);
	pinMode(LOOP3_LED_PIN, OUTPUT);
	pinMode(LOOP4_LED_PIN, OUTPUT);

	// press event handlers
	ampSwitchButton.attachClick([](void *ctx)
								{ ((Pushbuttons *)(ctx))->handlePress(0); }, this);
	loop1Button.attachClick([](void *ctx)
							{ ((Pushbuttons *)(ctx))->handlePress(1); }, this);
	loop2Button.attachClick([](void *ctx)
							{ ((Pushbuttons *)(ctx))->handlePress(2); }, this);
	loop3Button.attachClick([](void *ctx)
							{ ((Pushbuttons *)(ctx))->handlePress(3); }, this);
	loop4Button.attachClick([](void *ctx)
							{ ((Pushbuttons *)(ctx))->handlePress(4); }, this);
}

void Pushbuttons::Tick()
{
	ampSwitchButton.tick();
	loop1Button.tick();
	loop2Button.tick();
	loop3Button.tick();
	loop4Button.tick();
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

void Pushbuttons::handlePress(int buttonIndex)
{
	switch (buttonIndex)
	{
	case 0:
		ampSwitchPressed = !ampSwitchPressed;
		break;
	case 1:
		loop1Pressed = !loop1Pressed;
		break;
	case 2:
		loop2Pressed = !loop2Pressed;
		break;
	case 3:
		loop3Pressed = !loop3Pressed;
		break;
	case 4:
		loop4Pressed = !loop4Pressed;
		break;
	}

	toggleLeds();

	// auto preset = presetStore.Read(banks.GetCurrentBank(), banks.GetCurrentPreset());
	// editTracker.SetPreset(preset);

	// preset.Print();
}

void Pushbuttons::toggleLeds()
{
	digitalWrite(AMP_SWITCH_LED_PIN, ampSwitchPressed ? HIGH : LOW);
	digitalWrite(LOOP1_LED_PIN, loop1Pressed ? HIGH : LOW);
	digitalWrite(LOOP2_LED_PIN, loop2Pressed ? HIGH : LOW);
	digitalWrite(LOOP3_LED_PIN, loop3Pressed ? HIGH : LOW);
	digitalWrite(LOOP4_LED_PIN, loop4Pressed ? HIGH : LOW);
}