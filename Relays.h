#ifndef RELAYS_H
#define RELAYS_H

#include "Preset.h"

#define RELAY_AMPSWITCH_PIN 27
#define RELAY_BYPASS_PIN 26
#define RELAY_LOOP1_PIN 28
#define RELAY_LOOP2_PIN 29
#define RELAY_LOOP3_PIN 30
#define RELAY_LOOP4_PIN 31

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