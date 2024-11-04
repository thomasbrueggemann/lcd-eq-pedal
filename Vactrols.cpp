#include "Vactrols.h"

Vactrols::Vactrols()
{
	pinMode(BASS_POT_CS, OUTPUT);
	pinMode(MID_POT_CS, OUTPUT);
	pinMode(TREBLE_POT_CS, OUTPUT);
	pinMode(VOLUME_POT_CS, OUTPUT);
}

void Vactrols::ApplyPreset(Preset &preset)
{
	SetBass(preset.Bass);
	SetMiddle(preset.Middle);
	SetTreble(preset.Treble);
	SetVolume(preset.Volume);
}

void Vactrols::SetBass(int value)
{
	setDoubleVactrol(value, BASS_POT_CS, BASS_PWM1_PIN, BASS_PWM2_PIN, BassMiddleLookup);
}

void Vactrols::SetMiddle(int value)
{
	setDoubleVactrol(value, MID_POT_CS, MID_PWM1_PIN, MID_PWM2_PIN, BassMiddleLookup);
}

void Vactrols::SetTreble(int value)
{
	setDoubleVactrol(value, TREBLE_POT_CS, TREBLE_PWM1_PIN, TREBLE_PWM2_PIN, TrebleLookup);
}

void Vactrols::SetVolume(int value)
{
	auto mappedValue = map(value, 0, 1023, 0, 255);

	auto pwmValue = VolumeLookup[mappedValue][LOOKUP_PWM_IDX];
	auto potValue = VolumeLookup[mappedValue][LOOKUP_POT_IDX];

	setDigiPot(VOLUME_POT_CS, SINGLE_POT_ADDRESS, potValue);
	analogWrite(VOLUME_PWM1_PIN, pwmValue);
}

void Vactrols::setDoubleVactrol(int value, int csPin, int pwm1Pin, int pwm2Pin, int vactrolLookup[256][2])
{
	value = 1023 - value;
	auto mappedValue = map(value, 0, 1023, 0, 255);

	auto pwmValue = vactrolLookup[mappedValue][LOOKUP_PWM_IDX];
	auto potValue = vactrolLookup[mappedValue][LOOKUP_POT_IDX];

	setDigiPot(csPin, DOUBLE_POT_ADDRESS_A, potValue);
	analogWrite(pwm1Pin, pwmValue);

	auto inverseValue = 255 - mappedValue;
	auto inversePwmValue = vactrolLookup[inverseValue][LOOKUP_PWM_IDX];
	auto inversePotValue = vactrolLookup[inverseValue][LOOKUP_POT_IDX];

	setDigiPot(csPin, DOUBLE_POT_ADDRESS_B, potValue);
	analogWrite(pwm2Pin, inversePwmValue);
}

void Vactrols::setDigiPot(int csPin, int address, int value) 
{
	digitalWrite(csPin, LOW);
	SPI.transfer(address);
	SPI.transfer(value);
	digitalWrite(csPin, HIGH);
}