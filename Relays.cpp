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
  return;
	if (ampSwitchToggled != preset.AmpSwitch)
	{
		ampSwitchToggled = preset.AmpSwitch;
		digitalWrite(RELAY_AMPSWITCH_PIN, ampSwitchToggled ? HIGH : LOW);
	}

	if (loop1Toggled != preset.Loop1)
	{
		loop1Toggled = preset.Loop1;
		digitalWrite(RELAY_LOOP1_PIN, loop1Toggled ? HIGH : LOW);
	}

	if (loop2Toggled != preset.Loop2)
	{
		loop2Toggled = preset.Loop2;
		digitalWrite(RELAY_LOOP2_PIN, loop2Toggled ? HIGH : LOW);
	}

	if (loop3Toggled != preset.Loop3)
	{
		loop3Toggled = preset.Loop3;
		digitalWrite(RELAY_LOOP3_PIN, loop3Toggled ? HIGH : LOW);
	}

	if (loop4Toggled != preset.Loop4)
	{
		loop4Toggled = preset.Loop4;
		digitalWrite(RELAY_LOOP4_PIN, loop4Toggled ? HIGH : LOW);
	}
}

void Relays::UnBypass()
{
	digitalWrite(RELAY_BYPASS_PIN, HIGH);
}

void Relays::Bypass() 
{
  digitalWrite(RELAY_BYPASS_PIN, LOW);
}
