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
	setDoubleVactrol(value, BASS_POT_CS, BASS_PWM1_PIN, BASS_PWM2_PIN, &bassMidVactrolLookup);
}

void Vactrols::SetMiddle(int value)
{
	setDoubleVactrol(value, MID_POT_CS, MID_PWM1_PIN, MID_PWM2_PIN, &bassMidVactrolLookup);
}

void Vactrols::SetTreble(int value)
{
	setDoubleVactrol(value, TREBLE_POT_CS, TREBLE_PWM1_PIN, TREBLE_PWM2_PIN, &trebleVactrolLookup);
}

void Vactrols::SetVolume(int value)
{
	setSingleVactrol(value, VOLUME_POT_CS, VOLUME_PWM1_PIN, &volumeVactrolLookup);
}

void Vactrols::setSingleVactrol(int value, int csPin, int pwmPin, int vactrolLookup[256][2])
{
	auto mappedValue = map(value, 0, 1023, 0, 255);

	auto pwmValue = vactrolLookup[mappedValue];
	auto potValue = vactrolLookup[mappedValue];

	setDigitalPotValue(csPin, ADDRESS1, potValue);
	digitalWrite(pwmPin, pwmValue);
}

void Vactrols::setDoubleVactrol(int value, int csPin, int pwm1Pin, int pwm2Pin, int vactrolLookup[256][2])
{
	auto mappedValue = map(value, 0, 1023, 0, 255);

	auto pwmValue = vactrolLookup[mappedValue][0];
	auto potValue = vactrolLookup[mappedValue][1];

	setDigitalPotValue(csPin, ADDRESS1, potValue);
	digitalWrite(pwm1Pin, pwmValue);

	auto inverseValue = 255 - mappedValue;

	auto inversePwmValue = vactrolLookup[inverseValue][0];
	auto inversePotValue = vactrolLookup[inverseValue][1];

	setDigitalPotValue(csPin, ADDRESS2, inversePotValue);
	digitalWrite(pwm2Pin, inversePwmValue);
}

void Vactrols::setDigitalPotValue(int csPin, byte address, int value)
{
	digitalWrite(csPin, LOW);

	SPI.transfer(address);
	SPI.transfer(value);

	digitalWrite(csPin, HIGH);
}