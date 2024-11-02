#include <Arduino.h>
#include <SPI.h>
#include <OneButton.h>

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

static void handleFootswitchPress(OneButton *oneButton) {
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
  footswitches.HandlePress(footswitchIndex);

  banks.SetPreset(footswitchIndex);
  auto preset = presetStore.Read(banks.GetCurrentBank(), banks.GetCurrentPreset());
  
  Serial.println("Reading Bank: " + String(banks.GetCurrentBank()) + " Preset: " + String(banks.GetCurrentPreset()));
  preset.Print();

  editTracker.SetPreset(preset);
}

static void handleFootswitchLongPress(OneButton *oneButton) {
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());

  auto preset = editTracker.GetPreset();

  Serial.println("Bank: " + String(banks.GetCurrentBank()) + " Preset: " + String(banks.GetCurrentPreset()));
  preset.Print();

  presetStore.Write(banks.GetCurrentBank(), banks.GetCurrentPreset(), preset);

  footswitches.HandleLongPress(footswitchIndex);
}

static void handleFootswitchDoublePress(OneButton *oneButton) {
  int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
  if (footswitchIndex == 0) {
    banks.BankDown();
  } else if (footswitchIndex == 2) {
    banks.BankUp();
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("*** LCD EQ PEDAL ***");

  SPI.begin();
  lcd.Begin();

  footswitch1.setup(FOOTSWITCH_1_PIN, INPUT_PULLUP, true);
  footswitch1.setPressMs(LONG_PRESS_THRESHOLD);
  footswitch1.attachClick(handleFootswitchPress, &footswitch1);
  footswitch1.attachLongPressStart(handleFootswitchLongPress, &footswitch1);
  footswitch1.attachDoubleClick(handleFootswitchDoublePress, &footswitch1);

  footswitch2.setup(FOOTSWITCH_2_PIN, INPUT_PULLUP, true);
  footswitch2.setPressMs(LONG_PRESS_THRESHOLD);
  footswitch2.attachClick(handleFootswitchPress, &footswitch2);
  footswitch2.attachLongPressStart(handleFootswitchLongPress, &footswitch2);
  footswitch2.attachDoubleClick(handleFootswitchDoublePress, &footswitch2);

  footswitch3.setup(FOOTSWITCH_3_PIN, INPUT_PULLUP, true);
  footswitch3.setPressMs(LONG_PRESS_THRESHOLD);
  footswitch3.attachClick(handleFootswitchPress, &footswitch3);
  footswitch3.attachLongPressStart(handleFootswitchLongPress, &footswitch3);
  footswitch3.attachDoubleClick(handleFootswitchDoublePress, &footswitch3);
}

void loop() {
  auto analogPotValues = analogPots.Read();
  auto pushbuttonValues = pushbuttons.Read();

  auto preset = editTracker.TrackChanges(analogPotValues, pushbuttonValues);

  relays.Toggle(preset);
  lcd.Draw(preset, banks.GetCurrentBank());
  vactrols.ApplyPreset(preset);
  pushbuttons.ApplyPreset(preset);

  analogPots.Tick();
  pushbuttons.Tick();

  footswitch1.tick();
  footswitch2.tick();
  footswitch3.tick();
}
