#ifndef RELAYS_H
#define RELAYS_H

#include "Preset.h"

#define RELAY_AMPSWITCH_PIN 12
#define RELAY_LOOP1_PIN 11
#define RELAY_LOOP2_PIN 10

class Relays
{
public:
	Relays();
	void Toggle(Preset &preset);

private:
};

#endif // RELAYS_H