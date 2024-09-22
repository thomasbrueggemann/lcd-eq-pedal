#ifndef FOOTSWITCHES_H
#define FOOTSWITCHES_H

#include <Arduino.h>

#include "Button2.h"
#include "Banks.h"
#include "Pins.h"
#include "Pots.h"
#include "PresetStore.h"
#include "Faders.h"

#define LONG_PRESS_TIME 1000
#define DOUBLE_CLICK_TIME 700

class Footswitches
{
public:
	Footswitches(Banks &banks, Pots &pots, Faders &faders);
	void Begin();
	void Loop();

private:
	Button2 footswitch1;
	Button2 footswitch2;
	Button2 footswitch3;
	Button2 footswitch4;

	Banks &banks;
	Pots &pots;
	Faders &faders;
	PresetStore presetStore;

	void checkFootswitch(Button2 &btn, byte footswitchId);

	void handlePress(byte footswitchId);
	void handleDoublePress(byte footswitchId);
	void handleLongPress(byte footswitchId);
};

#endif // FOOTSWITCHES_H