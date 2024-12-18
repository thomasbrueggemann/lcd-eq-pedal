#include "Relays.h"

Relays::Relays()
{
	pinMode(RELAY_AMPSWITCH_PIN, OUTPUT);
	pinMode(RELAY_BYPASS_PIN, OUTPUT);
	pinMode(RELAY_LOOP1_PIN, OUTPUT);
	pinMode(RELAY_LOOP2_PIN, OUTPUT);
	pinMode(RELAY_LOOP3_PIN, OUTPUT);
	pinMode(RELAY_LOOP4_PIN, OUTPUT);

	digitalWrite(RELAY_BYPASS_PIN, HIGH);
}

void Relays::Toggle(Preset &preset)
{
	if (ampSwitchToggled != preset.AmpSwitch)
	{
		ampSwitchToggled = preset.AmpSwitch;

		if (ampSwitchToggled)
		{
			digitalWrite(RELAY_AMPSWITCH_PIN, HIGH);
			delay(RELAY_SWITCH_DELAY);
		}
		else
		{
			digitalWrite(RELAY_AMPSWITCH_PIN, LOW);
		}
	}

	if (loop1Toggled != preset.Loop1)
	{
		loop1Toggled = preset.Loop1;

		if (loop1Toggled)
		{
			digitalWrite(RELAY_LOOP1_PIN, HIGH);
			delay(RELAY_SWITCH_DELAY);
		}
		else
		{
			digitalWrite(RELAY_LOOP1_PIN, LOW);
		}
	}

	if (loop2Toggled != preset.Loop2)
	{
		loop2Toggled = preset.Loop2;

		if (loop2Toggled)
		{
			digitalWrite(RELAY_LOOP2_PIN, HIGH);
			delay(RELAY_SWITCH_DELAY);
		}
		else
		{
			digitalWrite(RELAY_LOOP2_PIN, LOW);
		}
	}

	if (loop3Toggled != preset.Loop3)
	{
		loop3Toggled = preset.Loop3;

		if (loop3Toggled)
		{
			digitalWrite(RELAY_LOOP3_PIN, HIGH);
			delay(RELAY_SWITCH_DELAY);
		}
		else
		{
			digitalWrite(RELAY_LOOP3_PIN, LOW);
		}
	}

	if (loop4Toggled != preset.Loop4)
	{
		loop4Toggled = preset.Loop4;

		if (loop4Toggled)
		{
			digitalWrite(RELAY_LOOP4_PIN, HIGH);
			delay(RELAY_SWITCH_DELAY);
		}
		else
		{
			digitalWrite(RELAY_LOOP4_PIN, LOW);
		}
	}
}

void Relays::UnBypass()
{
	digitalWrite(RELAY_BYPASS_PIN, HIGH);
	delay(RELAY_SWITCH_DELAY);
}

void Relays::Bypass()
{
	digitalWrite(RELAY_BYPASS_PIN, LOW);
}
