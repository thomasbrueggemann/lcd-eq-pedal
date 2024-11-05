#ifndef FOOTSWITCHES_H
#define FOOTSWITCHES_H

#include <Arduino.h>

#include "Banks.h"
#include "PresetStore.h"
#include "EditTracker.h"

#define LONG_PRESS_THRESHOLD 1000
#define LED_BLINK_TIMES 4
#define LED_BLINK_DELAY 80

#define FOOTSWITCH_1_PIN 4
#define FOOTSWITCH_2_PIN 5
#define FOOTSWITCH_3_PIN 6

#define FOOTSWITCH_1_LED_B_PIN 44
#define FOOTSWITCH_2_LED_B_PIN 46
#define FOOTSWITCH_3_LED_B_PIN 48

#define FOOTSWITCH_1_LED_A_PIN 45
#define FOOTSWITCH_2_LED_A_PIN 47
#define FOOTSWITCH_3_LED_A_PIN 49

enum FootswitchesState
{
	INACTIVE,
	ACTIVE_A,
	ACTIVE_B
};

class Footswitches
{
public:
	Footswitches();

	int GetPresetIndex(int footswitchIndex);
	void HandlePress(int footswitchIndex);
	void HandleLongPress(int footswitchIndex);

	int PinToIndex(int pin);

private:
	int footswitch1ActiveLedPin = FOOTSWITCH_1_LED_A_PIN;
	int footswitch2ActiveLedPin = FOOTSWITCH_2_LED_A_PIN;
	int footswitch3ActiveLedPin = FOOTSWITCH_3_LED_A_PIN;

	int footswitch1InactiveLedPin = FOOTSWITCH_1_LED_B_PIN;
	int footswitch2InactiveLedPin = FOOTSWITCH_2_LED_B_PIN;
	int footswitch3InactiveLedPin = FOOTSWITCH_3_LED_B_PIN;

	FootswitchesState footswitch1State = INACTIVE;
	FootswitchesState footswitch2State = INACTIVE;
	FootswitchesState footswitch3State = INACTIVE;

	void toggleLeds(int footswitchIndex);
	void blinkLeds(int footswitchIndex);
	void blinkLed(int ledPin);
};

#endif // FOOTSWITCHES_H