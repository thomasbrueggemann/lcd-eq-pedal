#include "Footswitches.h"

Footswitches::Footswitches()
{
	pinMode(FOOTSWITCH_1_LED_A_PIN, OUTPUT);
	pinMode(FOOTSWITCH_2_LED_A_PIN, OUTPUT);
	pinMode(FOOTSWITCH_3_LED_A_PIN, OUTPUT);

	pinMode(FOOTSWITCH_1_LED_B_PIN, OUTPUT);
	pinMode(FOOTSWITCH_2_LED_B_PIN, OUTPUT);
	pinMode(FOOTSWITCH_3_LED_B_PIN, OUTPUT);
}

int Footswitches::PinToIndex(int pin)
{
	switch (pin)
	{
	case FOOTSWITCH_1_PIN:
		return 0;
	case FOOTSWITCH_2_PIN:
		return 1;
	case FOOTSWITCH_3_PIN:
		return 2;
	}
}

int Footswitches::HandlePress(int footswitchIndex)
{
	int presetIndex = 0;

	switch (footswitchIndex)
	{
	case 0:

		if (footswitch1State == ACTIVE_B || footswitch1State == INACTIVE)
		{
			footswitch1State = ACTIVE_A;
			footswitch1ActiveLedPin = FOOTSWITCH_1_LED_A_PIN;
			footswitch1InactiveLedPin = FOOTSWITCH_1_LED_B_PIN;
			presetIndex = 0;
		}
		else
		{
			footswitch1State = ACTIVE_B;
			footswitch1ActiveLedPin = FOOTSWITCH_1_LED_B_PIN;
			footswitch1InactiveLedPin = FOOTSWITCH_1_LED_A_PIN;
			presetIndex = 1;
		}

		footswitch2State = INACTIVE;
		footswitch3State = INACTIVE;

		break;
	case 1:
		if (footswitch2State == ACTIVE_B || footswitch2State == INACTIVE)
		{
			footswitch2State = ACTIVE_A;
			footswitch2ActiveLedPin = FOOTSWITCH_2_LED_A_PIN;
			footswitch2InactiveLedPin = FOOTSWITCH_2_LED_B_PIN;
			presetIndex = 2;
		}
		else
		{
			footswitch2State = ACTIVE_B;
			footswitch2ActiveLedPin = FOOTSWITCH_2_LED_B_PIN;
			footswitch2InactiveLedPin = FOOTSWITCH_2_LED_A_PIN;
			presetIndex = 3;
		}

		footswitch1State = INACTIVE;
		footswitch3State = INACTIVE;

		break;
	case 2:

		if (footswitch3State == ACTIVE_B || footswitch3State == INACTIVE)
		{
			footswitch3State = ACTIVE_A;
			footswitch3ActiveLedPin = FOOTSWITCH_3_LED_A_PIN;
			footswitch3InactiveLedPin = FOOTSWITCH_3_LED_B_PIN;
			presetIndex = 4;
		}
		else
		{
			footswitch3State = ACTIVE_B;
			footswitch3ActiveLedPin = FOOTSWITCH_3_LED_B_PIN;
			footswitch3InactiveLedPin = FOOTSWITCH_3_LED_A_PIN;
			presetIndex = 5;
		}

		footswitch1State = INACTIVE;
		footswitch2State = INACTIVE;

		break;
	}

	toggleLeds(footswitchIndex);

	return presetIndex;
}

void Footswitches::HandleLongPress(int footswitchIndex)
{
	blinkLeds(footswitchIndex);
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