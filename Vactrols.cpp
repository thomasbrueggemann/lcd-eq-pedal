#include "Vactrols.h"

Vactrols::Vactrols()
	: bassPot(BASS_POT_CS, 255, &SPI),
	  midPot(MID_POT_CS, 255, &SPI),
	  treblePot(TREBLE_POT_CS, 255, &SPI)
{
	pinMode(BASS_POT_CS, OUTPUT);
	pinMode(MID_POT_CS, OUTPUT);
	pinMode(TREBLE_POT_CS, OUTPUT);
	pinMode(VOLUME_POT_CS, OUTPUT);

	bassPot.begin();
	midPot.begin();
	treblePot.begin();
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
	setDoubleVactrol(value, bassPot, BASS_PWM1_PIN, BASS_PWM2_PIN, BassMiddleLookup);
}

void Vactrols::SetMiddle(int value)
{
	setDoubleVactrol(value, midPot, MID_PWM1_PIN, MID_PWM2_PIN, BassMiddleLookup);
}

void Vactrols::SetTreble(int value)
{
	setDoubleVactrol(value, treblePot, TREBLE_PWM1_PIN, TREBLE_PWM2_PIN, TrebleLookup);
}

void Vactrols::SetVolume(int value)
{
	auto mappedValue = map(value, 0, 1023, 0, 255);

	auto pwmValue = VolumeLookup[mappedValue];
	auto potValue = VolumeLookup[mappedValue];

	digitalWrite(VOLUME_POT_CS, LOW);
	SPI.transfer(ADDRESS);
	SPI.transfer(potValue);
	digitalWrite(VOLUME_POT_CS, HIGH);

	digitalWrite(VOLUME_PWM1_PIN, pwmValue);
}

void Vactrols::setDoubleVactrol(int value, MCP4261 &digipot, int pwm1Pin, int pwm2Pin, int vactrolLookup[256][2])
{
	auto mappedValue = map(value, 0, 1023, 0, 255);

	auto pwmValue = vactrolLookup[mappedValue][0];
	auto potValue = vactrolLookup[mappedValue][1];

	Serial.print("pwmValue: ");
	Serial.println(pwmValue);
	Serial.print("potValue: ");
	Serial.println(potValue);

	digipot.setValue(0, potValue);
	digitalWrite(pwm1Pin, pwmValue);

	auto inverseValue = 255 - mappedValue;

	auto inversePwmValue = vactrolLookup[inverseValue][0];
	auto inversePotValue = vactrolLookup[inverseValue][1];

	Serial.print("inversePwmValue: ");
	Serial.println(inversePwmValue);
	Serial.print("inversePotValue: ");
	Serial.println(inversePotValue);
	Serial.println("----------------");

	digipot.setValue(1, inversePwmValue);
	digitalWrite(pwm2Pin, inversePwmValue);
}