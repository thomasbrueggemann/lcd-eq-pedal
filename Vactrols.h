#ifndef VACTROLS_H
#define VACTROLS_H

#include <Arduino.h>
#include <SPI.h>

#include "VactrolLookup.h"
#include "Preset.h"

#define ADDRESS1 0x11
#define ADDRESS2 0x12

#define TREBLE_POT_CS 10
#define TREBLE_PWM1_PIN 9
#define TREBLE_PWM2_PIN 8

#define MID_POT_CS 11
#define MID_PWM1_PIN 7
#define MID_PWM2_PIN 6

#define BASS_POT_CS 12
#define BASS_PWM1_PIN 5
#define BASS_PWM2_PIN 4

#define VOLUME_POT_CS 13
#define VOLUME_PWM1_PIN 3

class Vactrols
{
public:
	// Constructor
	Vactrols();

	void ApplyPreset(Preset &preset);

	void SetBass(int value);
	void SetMiddle(int value);
	void SetTreble(int value);
	void SetVolume(int value);

private:
	void setDigitalPotValue(int csPin, byte address, int value);
	void setSingleVactrol(int value, int csPin, int pwmPin, int vactrolLookup[256][2]);
	void setDoubleVactrol(int value, int csPin, int pwm1Pin, int pwm2Pin, int vactrolLookup[256][2]);
};

#endif // VACTROLS_H