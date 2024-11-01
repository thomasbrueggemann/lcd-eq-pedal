#include "Footswitches.h"

Footswitches::Footswitches(Banks &bank, PresetStore &presetStore, EditTracker &editTracker)
	: footswitch1(FOOTSWITCH_1_PIN, true, true),
	  footswitch2(FOOTSWITCH_2_PIN, true, true),
	  footswitch3(FOOTSWITCH_3_PIN, true, true),
	  banks(banks),
	  presetStore(presetStore),
	  editTracker(editTracker)
{
	pinMode(FOOTSWITCH_1_LED_A_PIN, OUTPUT);
	pinMode(FOOTSWITCH_2_LED_A_PIN, OUTPUT);
	pinMode(FOOTSWITCH_3_LED_A_PIN, OUTPUT);

	pinMode(FOOTSWITCH_1_LED_B_PIN, OUTPUT);
	pinMode(FOOTSWITCH_2_LED_B_PIN, OUTPUT);
	pinMode(FOOTSWITCH_3_LED_B_PIN, OUTPUT);

	// configure long press threshold
	footswitch1.setPressMs(LONG_PRESS_THRESHOLD);
	footswitch2.setPressMs(LONG_PRESS_THRESHOLD);
	footswitch3.setPressMs(LONG_PRESS_THRESHOLD);

	// press event handlers
	footswitch1.attachClick([](void *ctx)
							{ ((Footswitches *)(ctx))->handlePress(0); }, this);
	footswitch2.attachClick([](void *ctx)
							{ ((Footswitches *)(ctx))->handlePress(1); }, this);
	footswitch3.attachClick([](void *ctx)
							{ ((Footswitches *)(ctx))->handlePress(2); }, this);

	// long press event handlers
	footswitch1.attachLongPressStart([](void *ctx)
									 { ((Footswitches *)(ctx))->handleLongPress(0); }, this);
	footswitch2.attachLongPressStart([](void *ctx)
									 { ((Footswitches *)(ctx))->handleLongPress(1); }, this);
	footswitch3.attachLongPressStart([](void *ctx)
									 { ((Footswitches *)(ctx))->handleLongPress(2); }, this);

	// double click event handlers (only for footswitch 1 and 3, to handle the banking)
	footswitch1.attachDoubleClick([](void *ctx)
								  { ((Footswitches *)(ctx))->handleDoubleClick(0); }, this);
	footswitch3.attachDoubleClick([](void *ctx)
								  { ((Footswitches *)(ctx))->handleDoubleClick(2); }, this);
}

void Footswitches::Tick()
{
	footswitch1.tick();
	footswitch2.tick();
	footswitch3.tick();
}

void Footswitches::handlePress(int footswitchIndex)
{
	bool hiddenPresetEnabled = false;

	// if we're re-pressing the same footswitch, toggle the hidden preset
	if (footswitchIndex != banks.GetCurrentPreset())
	{
		toggleHiddenPreset(footswitchIndex);
		hiddenPresetEnabled = true;
	}
	else
	{
		resetHiddenPresets();
	}

	int presetIndex = (footswitchIndex * 2) + (hiddenPresetEnabled == true ? 1 : 0);

	banks.SetPreset(presetIndex);
	toggleLeds(footswitchIndex);

	auto preset = presetStore.Read(banks.GetCurrentBank(), banks.GetCurrentPreset());
	editTracker.SetPreset(preset);

	preset.Print();
}

void Footswitches::handleLongPress(int footswitchIndex)
{
  Serial.println("Longpress");
  Serial.println(footswitchIndex);
  Serial.println(banks.GetCurrentPreset());
  Serial.println("##");

	// long press is only available on the current preset
	if (footswitchIndex != banks.GetCurrentPreset())
	{
		return;
	}

	auto preset = editTracker.GetPreset();
	presetStore.Write(banks.GetCurrentBank(), banks.GetCurrentPreset(), preset);

	blinkLeds(footswitchIndex);
}

void Footswitches::handleDoubleClick(int footswitchIndex)
{
	resetHiddenPresets();

	if (footswitchIndex == 0)
	{
		banks.BankDown();
	}
	else if (footswitchIndex == 2)
	{
		banks.BankUp();
	}
}

void Footswitches::toggleHiddenPreset(int footswitchIndex)
{
	switch (footswitchIndex)
	{
	case 0:
		footswitch1HiddenPresetEnabled = !footswitch1HiddenPresetEnabled;
		footswitch1ActiveLedPin = footswitch1HiddenPresetEnabled ? FOOTSWITCH_1_LED_B_PIN : FOOTSWITCH_1_LED_A_PIN;
		footswitch1InactiveLedPin = footswitch1HiddenPresetEnabled ? FOOTSWITCH_1_LED_A_PIN : FOOTSWITCH_1_LED_B_PIN;
		break;
	case 1:
		footswitch2HiddenPresetEnabled = !footswitch2HiddenPresetEnabled;
		footswitch2ActiveLedPin = footswitch2HiddenPresetEnabled ? FOOTSWITCH_2_LED_B_PIN : FOOTSWITCH_2_LED_A_PIN;
		footswitch2InactiveLedPin = footswitch2HiddenPresetEnabled ? FOOTSWITCH_2_LED_A_PIN : FOOTSWITCH_2_LED_B_PIN;
		break;
	case 2:
		footswitch3HiddenPresetEnabled = !footswitch3HiddenPresetEnabled;
		footswitch3ActiveLedPin = footswitch3HiddenPresetEnabled ? FOOTSWITCH_3_LED_B_PIN : FOOTSWITCH_3_LED_A_PIN;
		footswitch3InactiveLedPin = footswitch3HiddenPresetEnabled ? FOOTSWITCH_3_LED_A_PIN : FOOTSWITCH_3_LED_B_PIN;
		break;
	}
}

void Footswitches::resetHiddenPresets()
{
	footswitch1HiddenPresetEnabled = false;
	footswitch2HiddenPresetEnabled = false;
	footswitch3HiddenPresetEnabled = false;

	footswitch1ActiveLedPin = FOOTSWITCH_1_LED_A_PIN;
	footswitch2ActiveLedPin = FOOTSWITCH_2_LED_A_PIN;
	footswitch3ActiveLedPin = FOOTSWITCH_3_LED_A_PIN;

	footswitch1InactiveLedPin = FOOTSWITCH_1_LED_B_PIN;
	footswitch2InactiveLedPin = FOOTSWITCH_2_LED_B_PIN;
	footswitch3InactiveLedPin = FOOTSWITCH_3_LED_B_PIN;
}

void Footswitches::toggleLeds(int footswitchIndex)
{
	digitalWrite(footswitch1InactiveLedPin, LOW);
	digitalWrite(footswitch2InactiveLedPin, LOW);
	digitalWrite(footswitch3InactiveLedPin, LOW);

	switch (footswitchIndex)
	{
	case 0:
		digitalWrite(footswitch1ActiveLedPin, HIGH);
		digitalWrite(footswitch2ActiveLedPin, LOW);
		digitalWrite(footswitch3ActiveLedPin, LOW);
		break;
	case 1:
		digitalWrite(footswitch1ActiveLedPin, LOW);
		digitalWrite(footswitch2ActiveLedPin, HIGH);
		digitalWrite(footswitch3ActiveLedPin, LOW);
		break;
	case 2:
		digitalWrite(footswitch1ActiveLedPin, LOW);
		digitalWrite(footswitch2ActiveLedPin, LOW);
		digitalWrite(footswitch3ActiveLedPin, HIGH);
		break;
	}
}

void Footswitches::blinkLeds(int footswitchIndex)
{
	switch (footswitchIndex)
	{
	case 0:
		digitalWrite(footswitch2ActiveLedPin, LOW);
		digitalWrite(footswitch3ActiveLedPin, LOW);
		blinkLed(footswitch1ActiveLedPin);
		break;
	case 1:
		digitalWrite(footswitch1ActiveLedPin, LOW);
		digitalWrite(footswitch3ActiveLedPin, LOW);
		blinkLed(footswitch2ActiveLedPin);
		break;
	case 2:
		digitalWrite(footswitch1ActiveLedPin, LOW);
		digitalWrite(footswitch2ActiveLedPin, LOW);
		blinkLed(footswitch3ActiveLedPin);
		break;
	}
}

void Footswitches::blinkLed(int ledPin)
{
	for (int i = 0; i < LED_BLINK_TIMES; i++)
	{
		digitalWrite(ledPin, HIGH);
		delay(LED_BLINK_DELAY);
		digitalWrite(ledPin, LOW);
		delay(LED_BLINK_DELAY);
	}

	digitalWrite(ledPin, HIGH);
}