#include <Arduino.h>
#include <SPI.h>
#include <OneButton.h>

#include "Debug.h"
#include "LCD.h"
#include "AnalogPots.h"
#include "Banks.h"
#include "Footswitches.h"
#include "PresetStore.h"
#include "EditTracker.h"
#include "Relays.h"
#include "Vactrols.h"
#include "Pushbuttons.h"
#include "Preset.h"

#define COOLDOWN_LIMIT 500
#define SINGLE_PRESS_THRESHOLD 300
#define LONG_PRESS_THRESHOLD 600

LCD lcd;
Relays relays;
Vactrols vactrols;
AnalogPots analogPots;
Banks banks;
EditTracker editTracker;
PresetStore presetStore;
Footswitches footswitches;
Pushbuttons pushbuttons;

OneButton footswitch1;
OneButton footswitch2;
OneButton footswitch3;

OneButton ampSwitchButton;
OneButton loop1Button;
OneButton loop2Button;
OneButton loop3Button;
OneButton loop4Button;

static void applyPreset(Preset &preset)
{
  vactrols.ApplyPreset(preset);
  relays.Toggle(preset);
  pushbuttons.ApplyPreset(preset);

  delay(50);
  lcd.Draw(preset, banks.GetCurrentBank());
}

static void loadPreset(int footswitchIndex)
{
  int presetIdx = footswitches.GetPresetIndex(footswitchIndex);
  auto preset = presetStore.Read(presetIdx);

  D_println(presetIdx);
  applyPreset(preset);

  editTracker.SetPreset(preset);
  footswitches.HandlePress(footswitchIndex);
  banks.SetPreset(presetIdx);
}

static void handleFootswitchPress(OneButton *oneButton)
{
  D_print("Footswitch pressed:");
  D_println(oneButton->pin());
  
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
  loadPreset(footswitchIndex);
}

static void handleFootswitchLongPress(OneButton *oneButton)
{
  D_println("Footswitch long pressed");

  auto preset = editTracker.GetPreset();
  presetStore.Write(banks.GetCurrentBank(), banks.GetCurrentPreset(), preset);

  int footswitchIndex = banks.GetCurrentPreset() / 2;

  footswitches.HandleLongPress(footswitchIndex);
}

static void handleFootswitchDoublePress(OneButton *oneButton)
{
  D_println("Footswitch double pressed");
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
  if (footswitchIndex == 0)
  {
    banks.BankDown();
  }
  else if (footswitchIndex == 2)
  {
    banks.BankUp();
  }

  footswitches.ResetState();
  presetStore.PreloadBank(banks.GetCurrentBank());
  loadPreset(0);
}

static void handlePushbuttonPress(OneButton *oneButton)
{
  D_println("Pushbutton");
  pushbuttons.HandlePress(oneButton->pin());
}

void setup()
{
  D_SerialBegin(9600);
  D_println("*** LCD EQ PEDAL ***");

  SPI.begin();

  D_println("SPI initialized...");

  lcd.Begin();

  D_println("LCD initialized...");

  // Footswitches
  footswitch1.setup(FOOTSWITCH_1_PIN, INPUT_PULLUP, true);
  footswitch2.setup(FOOTSWITCH_2_PIN, INPUT_PULLUP, true);
  footswitch3.setup(FOOTSWITCH_3_PIN, INPUT_PULLUP, true);

  // Attach callbacks for footswitches
  footswitch1.attachPress(handleFootswitchPress, &footswitch1);
  footswitch1.attachLongPressStart(handleFootswitchDoublePress, &footswitch1);

  footswitch2.attachPress(handleFootswitchPress, &footswitch2);
  footswitch2.attachLongPressStart(handleFootswitchDoublePress, &footswitch2);

  footswitch3.attachPress(handleFootswitchPress, &footswitch3);
  footswitch3.attachLongPressStart(handleFootswitchDoublePress, &footswitch3);

  // Setup other buttons
  ampSwitchButton.setup(AMP_SWITCH_BUTTON_PIN, INPUT_PULLUP, true);
  loop1Button.setup(LOOP1_BUTTON_PIN, INPUT_PULLUP, true);
  loop2Button.setup(LOOP2_BUTTON_PIN, INPUT_PULLUP, true);
  loop3Button.setup(LOOP3_BUTTON_PIN, INPUT_PULLUP, true);
  loop4Button.setup(LOOP4_BUTTON_PIN, INPUT_PULLUP, true);

  // Attach callbacks for other buttons
  ampSwitchButton.attachClick(handlePushbuttonPress, &ampSwitchButton);
  ampSwitchButton.attachLongPressStart(handleFootswitchLongPress, &ampSwitchButton);
  
  loop1Button.attachClick(handlePushbuttonPress, &loop1Button);
  loop2Button.attachClick(handlePushbuttonPress, &loop2Button);
  loop3Button.attachClick(handlePushbuttonPress, &loop3Button);
  loop4Button.attachClick(handlePushbuttonPress, &loop4Button);

  presetStore.PreloadBank(banks.GetCurrentBank());
  loadPreset(0);

  relays.UnBypass();
}

int cooldownCounter = 0;

void loop()
{
  if (cooldownCounter == 0)
  {
    auto analogPotValues = analogPots.Read();
    auto pushbuttonValues = pushbuttons.Read();

    auto preset = editTracker.TrackChanges(analogPotValues, pushbuttonValues);

    if (preset.PresetChanged)
    {
      cooldownCounter = 0;
      applyPreset(preset);
    }
    else
    {
      cooldownCounter = COOLDOWN_LIMIT;
    }
  }
  else
  {
    cooldownCounter--;
  }

  analogPots.Tick();
  ampSwitchButton.tick();
  loop1Button.tick();
  loop2Button.tick();
  loop3Button.tick();
  loop4Button.tick();

  footswitch1.tick();
  footswitch2.tick();
  footswitch3.tick();
}
