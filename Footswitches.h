#ifndef FOOTSWITCHES_H
#define FOOTSWITCHES_H

#include <Arduino.h>
#include <OneButton.h>

#include "Banks.h"
#include "PresetStore.h"
#include "EditTracker.h"

#define LONG_PRESS_THRESHOLD 1000
#define LED_BLINK_TIMES 4
#define LED_BLINK_DELAY 80

#define FOOTSWITCH_1_PIN 40
#define FOOTSWITCH_2_PIN 42
#define FOOTSWITCH_3_PIN 44

#define FOOTSWITCH_1_LED_PIN 41
#define FOOTSWITCH_2_LED_PIN 43
#define FOOTSWITCH_3_LED_PIN 45

class Footswitches
{
public:
	Footswitches(Banks &banks, PresetStore &presetStore, EditTracker &editTracker);

	void Tick();

private:
	OneButton footswitch1;
	OneButton footswitch2;
	OneButton footswitch3;

	Banks &banks;
	PresetStore &presetStore;
	EditTracker &editTracker;

	void handlePress(int footswitchIndex);
	void handleLongPress(int footswitchIndex);
	void handleDoubleClick(int footswitchIndex);

	void toggleLeds(int footswitchIndex);
	void blinkLeds(int footswitchIndex);
	void blinkLed(int ledPin);
};

#endif // FOOTSWITCHES_H