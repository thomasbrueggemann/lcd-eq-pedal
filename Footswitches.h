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

#define FOOTSWITCH_1_PIN 41
#define FOOTSWITCH_2_PIN 42
#define FOOTSWITCH_3_PIN 43

#define FOOTSWITCH_1_LED_A_PIN 44
#define FOOTSWITCH_2_LED_A_PIN 45
#define FOOTSWITCH_3_LED_A_PIN 46

#define FOOTSWITCH_1_LED_B_PIN 47
#define FOOTSWITCH_2_LED_B_PIN 48
#define FOOTSWITCH_3_LED_B_PIN 49

class Footswitches
{
public:
	Footswitches(Banks &banks, PresetStore &presetStore, EditTracker &editTracker);

	void Tick();

private:
	OneButton footswitch1;
	OneButton footswitch2;
	OneButton footswitch3;

	bool footswitch1HiddenPresetEnabled = false;
	bool footswitch2HiddenPresetEnabled = false;
	bool footswitch3HiddenPresetEnabled = false;

	int footswitch1ActiveLedPin = FOOTSWITCH_1_LED_A_PIN;
	int footswitch2ActiveLedPin = FOOTSWITCH_2_LED_A_PIN;
	int footswitch3ActiveLedPin = FOOTSWITCH_3_LED_A_PIN;

	int footswitch1InactiveLedPin = FOOTSWITCH_1_LED_B_PIN;
	int footswitch2InactiveLedPin = FOOTSWITCH_2_LED_B_PIN;
	int footswitch3InactiveLedPin = FOOTSWITCH_3_LED_B_PIN;

	Banks &banks;
	PresetStore &presetStore;
	EditTracker &editTracker;

	void handlePress(int footswitchIndex);
	void handleLongPress(int footswitchIndex);
	void handleDoubleClick(int footswitchIndex);

	void toggleLeds(int footswitchIndex);
	void blinkLeds(int footswitchIndex);
	void blinkLed(int ledPin);

	void toggleHiddenPreset(int footswitchIndex);
	void resetHiddenPresets();
};

#endif // FOOTSWITCHES_H