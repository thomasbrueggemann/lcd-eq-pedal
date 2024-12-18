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

  applyPreset(preset);

  editTracker.SetPreset(preset);
  footswitches.HandlePress(footswitchIndex);
  banks.SetPreset(presetIdx);
}

static void handleFootswitchPress(OneButton *oneButton)
{
  D_println("Footswitch pressed");
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
  loadPreset(footswitchIndex);
}

static void handleFootswitchLongPress(OneButton *oneButton)
{
  D_println("Footswitch long pressed");
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());

  auto preset = editTracker.GetPreset();
  presetStore.Write(banks.GetCurrentBank(), banks.GetCurrentPreset(), preset);

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
  pinMode(RESET_PIN, INPUT_PULLUP);  // Protect reset pin from noise

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

  // Set press threshold for all footswitches
  footswitch1.setPressMs(LONG_PRESS_THRESHOLD);
  footswitch2.setPressMs(LONG_PRESS_THRESHOLD);
  footswitch3.setPressMs(LONG_PRESS_THRESHOLD);

  footswitch1.setClickMs(SINGLE_PRESS_THRESHOLD);
  footswitch2.setClickMs(SINGLE_PRESS_THRESHOLD);
  footswitch3.setClickMs(SINGLE_PRESS_THRESHOLD);

  // Attach callbacks for footswitches
  footswitch1.attachClick(handleFootswitchPress, &footswitch1);
  footswitch1.attachLongPressStart(handleFootswitchLongPress, &footswitch1);
  footswitch1.attachDoubleClick(handleFootswitchDoublePress, &footswitch1);

  footswitch2.attachClick(handleFootswitchPress, &footswitch2);
  footswitch2.attachLongPressStart(handleFootswitchLongPress, &footswitch2);
  footswitch2.attachDoubleClick(handleFootswitchDoublePress, &footswitch2);

  footswitch3.attachClick(handleFootswitchPress, &footswitch3);
  footswitch3.attachLongPressStart(handleFootswitchLongPress, &footswitch3);
  footswitch3.attachDoubleClick(handleFootswitchDoublePress, &footswitch3);

  // Setup other buttons
  ampSwitchButton.setup(AMP_SWITCH_BUTTON_PIN, INPUT_PULLUP, true);
  loop1Button.setup(LOOP1_BUTTON_PIN, INPUT_PULLUP, true);
  loop2Button.setup(LOOP2_BUTTON_PIN, INPUT_PULLUP, true);
  loop3Button.setup(LOOP3_BUTTON_PIN, INPUT_PULLUP, true);
  loop4Button.setup(LOOP4_BUTTON_PIN, INPUT_PULLUP, true);

  // Attach callbacks for other buttons
  ampSwitchButton.attachPress(handlePushbuttonPress, &ampSwitchButton);
  loop1Button.attachPress(handlePushbuttonPress, &loop1Button);
  loop2Button.attachPress(handlePushbuttonPress, &loop2Button);
  loop3Button.attachPress(handlePushbuttonPress, &loop3Button);
  loop4Button.attachPress(handlePushbuttonPress, &loop4Button);

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
