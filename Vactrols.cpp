#include "Vactrols.h"

Vactrols::Vactrols() : volumeDAC(VOLUME_DAC_CS), bassDAC(BASS_DAC_CS), midDAC(MID_DAC_CS), trebleDAC(TREBLE_DAC_CS)
{
	volumeDAC.init();
	volumeDAC.turnOnChannelA();

	bassDAC.init();
	bassDAC.turnOnChannelA();
	bassDAC.turnOnChannelB();

	midDAC.init();
	midDAC.turnOnChannelA();
	midDAC.turnOnChannelB();

	trebleDAC.init();
	trebleDAC.turnOnChannelA();
	trebleDAC.turnOnChannelB();
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
	int countA = (sizeof(bass_a) / sizeof(bass_a[0])) - 1;
	auto mappedValueA = map(1023 - value, 0, 1023, 0, countA);

	int countB = (sizeof(bass_b) / sizeof(bass_b[0])) - 1;
	auto mappedValueB = map(value, 0, 1023, 0, countB);

	bassDAC.setVoltageA(bass_a[mappedValueA]);
	bassDAC.setVoltageB(bass_b[mappedValueB]);

	bassDAC.updateDAC();
}

void Vactrols::SetMiddle(int value)
{
	int countA = (sizeof(mid_a) / sizeof(mid_a[0])) - 1;
	auto mappedValueA = map(1023 - value, 0, 1023, 0, countA);

	int countB = (sizeof(mid_b) / sizeof(mid_b[0])) - 1;
	auto mappedValueB = map(value, 0, 1023, 0, countB);

	midDAC.setVoltageA(mid_a[mappedValueA]);
	midDAC.setVoltageB(mid_b[mappedValueB]);

	midDAC.updateDAC();
}

void Vactrols::SetTreble(int value)
{
	int countA = (sizeof(treble_a) / sizeof(treble_a[0])) - 1;
	auto mappedValueA = map(1023 - value, 0, 1023, 0, countA);

	int countB = (sizeof(treble_b) / sizeof(treble_b[0])) - 1;
	auto mappedValueB = map(value, 0, 1023, 0, countB);

	trebleDAC.setVoltageA(treble_a[mappedValueA]);
	trebleDAC.setVoltageB(treble_b[mappedValueB]);

	trebleDAC.updateDAC();
}

void Vactrols::SetVolume(int value)
{
	int countA = (sizeof(volume_a) / sizeof(volume_a[0])) - 1;
	auto mappedValueA = map(value, 0, 1023, 0, countA);
	volumeDAC.setVoltageA(volume_a[mappedValueA]);

	volumeDAC.updateDAC();
}