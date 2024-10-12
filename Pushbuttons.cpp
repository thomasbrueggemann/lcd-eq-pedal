#include "Pushbuttons.h"

Pushbuttons::Pushbuttons()
	: ampSwitchButton(AMP_SWITCH_BUTTON_PIN, true),
	  loop1Button(LOOP1_BUTTON_PIN, true),
	  loop2Button(LOOP2_BUTTON_PIN, true),
	  loop3Button(LOOP3_BUTTON_PIN, true),
	  loop4Button(LOOP4_BUTTON_PIN, true)
{
}

void Pushbuttons::Tick()
{
	ampSwitchButton.tick();
	loop1Button.tick();
	loop2Button.tick();
	loop3Button.tick();
	loop4Button.tick();
}