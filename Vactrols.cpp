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
	auto mappedValueA = map(1023 - value, 0, 1023, 0, 102);
	auto mappedValueB = map(value, 0, 1023, 0, 100);

	bassDAC.setVoltageA(bass_a[mappedValueA]);
	bassDAC.setVoltageB(bass_b[mappedValueB]);

	bassDAC.updateDAC();
}

void Vactrols::SetMiddle(int value)
{
	auto mappedValueA = map(1023 - value, 0, 1023, 0, 97);
	auto mappedValueB = map(value, 0, 1023, 0, 96);

	midDAC.setVoltageA(mid_a[mappedValueA]);
	midDAC.setVoltageB(mid_b[mappedValueB]);

	midDAC.updateDAC();
}

void Vactrols::SetTreble(int value)
{
	auto mappedValueA = map(1023 - value, 0, 1023, 0, 84);
	auto mappedValueB = map(value, 0, 1023, 0, 84);

	trebleDAC.setVoltageA(treble_a[mappedValueA]);
	trebleDAC.setVoltageB(treble_b[mappedValueB]);

	trebleDAC.updateDAC();
}

void Vactrols::SetVolume(int value)
{
	auto mappedValueA = map(value, 0, 1023, 0, 109);

  D_println(mappedValueA);

	volumeDAC.setVoltageA(volume_a[mappedValueA]);

	volumeDAC.updateDAC();
}