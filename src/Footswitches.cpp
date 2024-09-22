#include "Footswitches.h"
#include "Button2.h"

Footswitches::Footswitches(Banks &banks, Pots &pots, Faders &faders)
	: presetStore(),
	  banks(banks),
	  faders(faders),
	  pots(pots),
	  footswitch1(FOOTSWITCH_PIN_1),
	  footswitch2(FOOTSWITCH_PIN_2),
	  footswitch3(FOOTSWITCH_PIN_3),
	  footswitch4(FOOTSWITCH_PIN_4)
{
	footswitch1.setLongClickTime(LONG_PRESS_TIME);
	footswitch1.setDoubleClickTime(DOUBLE_CLICK_TIME);

	footswitch2.setLongClickTime(LONG_PRESS_TIME);
	footswitch2.setDoubleClickTime(DOUBLE_CLICK_TIME);

	footswitch3.setLongClickTime(LONG_PRESS_TIME);
	footswitch3.setDoubleClickTime(DOUBLE_CLICK_TIME);

	footswitch4.setLongClickTime(LONG_PRESS_TIME);
	footswitch4.setDoubleClickTime(DOUBLE_CLICK_TIME);
}

void Footswitches::Begin()
{
	Preset preset = presetStore.ReadPreset(banks.GetCurrentBank(), banks.GetCurrentPreset());
	preset.Print();

	pots.SetToPreset(preset);
	faders.MoveToPreset(preset);
}

void Footswitches::Loop()
{
	checkFootswitch(footswitch1, 0);
	checkFootswitch(footswitch2, 1);
	checkFootswitch(footswitch3, 2);
	checkFootswitch(footswitch4, 3);
}

void Footswitches::checkFootswitch(Button2 &footswitch, byte footswitchId)
{
	footswitch.loop();

	if (footswitch.wasPressed())
	{
		Serial.println("---");

		switch (footswitch.read())
		{
		case single_click:
			handlePress(footswitchId);
			break;
		case double_click:
			handleDoublePress(footswitchId);
			break;
		case long_click:
			handleLongPress(footswitchId);
			break;
		}
	}
}

void Footswitches::handlePress(byte footswitchId)
{
	Serial.print("Footswitch pressed: ");
	Serial.println(footswitchId);

	banks.SetPreset(footswitchId);

	Preset preset = presetStore.ReadPreset(banks.GetCurrentBank(), banks.GetCurrentPreset());
	preset.Print();

	pots.SetToPreset(preset);
	faders.MoveToPreset(preset);
}

void Footswitches::handleLongPress(byte footswitchId)
{
	Serial.print("Store preset for bank ");
	Serial.print(banks.GetCurrentBank());
	Serial.print(" and preset ");
	Serial.println(banks.GetCurrentPreset());

	Preset preset = faders.GetCurrentValues();
	preset.Print();

	presetStore.WritePreset(banks.GetCurrentBank(), banks.GetCurrentPreset(), preset);
}

void Footswitches::handleDoublePress(byte footswitchId)
{
	switch (footswitchId)
	{
	case 0:
		banks.BankDown();
		break;
	case 3:
		banks.BankUp();
		break;
	}
}