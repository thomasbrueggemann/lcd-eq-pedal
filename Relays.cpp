#include "Relays.h"

Relays::Relays()
{
	pinMode(RELAY_AMPSWITCH_PIN, OUTPUT);
	pinMode(RELAY_LOOP1_PIN, OUTPUT);
	pinMode(RELAY_LOOP2_PIN, OUTPUT);
}

void Relays::Toggle(Preset &preset)
{
	digitalWrite(RELAY_AMPSWITCH_PIN, preset.AmpSwitch ? HIGH : LOW);
	digitalWrite(RELAY_LOOP1_PIN, preset.Loop1 ? HIGH : LOW);
	digitalWrite(RELAY_LOOP2_PIN, preset.Loop2 ? HIGH : LOW);
}
