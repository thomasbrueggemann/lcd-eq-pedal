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
	digitalWrite(RELAY_AMPSWITCH_PIN, preset.AmpSwitch ? HIGH : LOW);
	digitalWrite(RELAY_LOOP1_PIN, preset.Loop1 ? HIGH : LOW);
	digitalWrite(RELAY_LOOP2_PIN, preset.Loop2 ? HIGH : LOW);
	digitalWrite(RELAY_LOOP3_PIN, preset.Loop3 ? HIGH : LOW);
	digitalWrite(RELAY_LOOP4_PIN, preset.Loop4 ? HIGH : LOW);
}

void Relays::UnBypass()
{
	digitalWrite(RELAY_BYPASS_PIN, HIGH);
}
