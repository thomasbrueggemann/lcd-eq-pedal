#ifndef RELAYS_H
#define RELAYS_H

#include "Preset.h"

#define RELAY_AMPSWITCH_PIN 50
#define RELAY_BYPASS_PIN 16
#define RELAY_LOOP1_PIN 11
#define RELAY_LOOP2_PIN 21
#define RELAY_LOOP3_PIN 18
#define RELAY_LOOP4_PIN 19

#define RELAY_SWITCH_DELAY 20

class Relays
{
public:
	Relays();
	void Toggle(Preset &preset);
	void UnBypass();
  void Bypass();

private:
	bool ampSwitchToggled = false;
	bool loop1Toggled = false;
	bool loop2Toggled = false;
	bool loop3Toggled = false;
	bool loop4Toggled = false;
};

#endif // RELAYS_H