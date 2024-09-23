#include "Footswitches.h"

Footswitches::Footswitches(Banks &banks)
	: footswitch1(FOOTSWITCH_1_PIN, true, true),
	  footswitch2(FOOTSWITCH_2_PIN, true, true),
	  footswitch3(FOOTSWITCH_3_PIN, true, true),
	  banks(banks)
{
	pinMode(FOOTSWITCH_1_LED_PIN, OUTPUT);
	pinMode(FOOTSWITCH_2_LED_PIN, OUTPUT);
	pinMode(FOOTSWITCH_3_LED_PIN, OUTPUT);

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
	Serial.print("Pressed ");
	Serial.println(footswitchIndex);

	banks.SetPreset(footswitchIndex);
	toggleLeds(footswitchIndex);
}

void Footswitches::handleLongPress(int footswitchIndex)
{
	// long press is only available on the current preset
	if (footswitchIndex != banks.GetCurrentPreset())
	{
		return;
	}

	Serial.print("Long Pressed ");
	Serial.println(footswitchIndex);

	blinkLeds(footswitchIndex);
}

void Footswitches::handleDoubleClick(int footswitchIndex)
{
	Serial.print("Double Clicked ");
	Serial.println(footswitchIndex);

	if (footswitchIndex == 0)
	{
		banks.BankDown();
	}
	else if (footswitchIndex == 2)
	{
		banks.BankUp();
	}
}

void Footswitches::toggleLeds(int footswitchIndex)
{
	switch (footswitchIndex)
	{
	case 0:
		digitalWrite(FOOTSWITCH_1_LED_PIN, HIGH);
		digitalWrite(FOOTSWITCH_2_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_3_LED_PIN, LOW);
		break;
	case 1:
		digitalWrite(FOOTSWITCH_1_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_2_LED_PIN, HIGH);
		digitalWrite(FOOTSWITCH_3_LED_PIN, LOW);
		break;
	case 2:
		digitalWrite(FOOTSWITCH_1_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_2_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_3_LED_PIN, HIGH);
		break;
	}
}

void Footswitches::blinkLeds(int footswitchIndex)
{
	switch (footswitchIndex)
	{
	case 0:
		digitalWrite(FOOTSWITCH_2_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_3_LED_PIN, LOW);
		blinkLed(FOOTSWITCH_1_LED_PIN);
		break;
	case 1:
		digitalWrite(FOOTSWITCH_1_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_3_LED_PIN, LOW);
		blinkLed(FOOTSWITCH_2_LED_PIN);
		break;
	case 2:
		digitalWrite(FOOTSWITCH_1_LED_PIN, LOW);
		digitalWrite(FOOTSWITCH_2_LED_PIN, LOW);
		blinkLed(FOOTSWITCH_3_LED_PIN);
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