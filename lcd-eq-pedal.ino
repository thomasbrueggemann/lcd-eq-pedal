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

bool forceApply = true;

static void loadPreset(int footswitchIndex)
{
    int presetIdx = footswitches.HandlePress(footswitchIndex);

    banks.SetPreset(presetIdx);
    auto preset = presetStore.Read(banks.GetCurrentBank(), banks.GetCurrentPreset());

    editTracker.SetPreset(preset);
    forceApply = true;
}

static void handleFootswitchPress(OneButton *oneButton)
{
    int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
    loadPreset(footswitchIndex);
}

static void handleFootswitchLongPress(OneButton *oneButton)
{
    int footswitchIndex = footswitches.PinToIndex(oneButton->pin());

    auto preset = editTracker.GetPreset();
    presetStore.Write(banks.GetCurrentBank(), banks.GetCurrentPreset(), preset);

    footswitches.HandleLongPress(footswitchIndex);
}

static void handleFootswitchDoublePress(OneButton *oneButton)
{
    int footswitchIndex = footswitches.PinToIndex(oneButton->pin());
    if (footswitchIndex == 0)
    {
        banks.BankDown();
    }
    else if (footswitchIndex == 2)
    {
        banks.BankUp();
    }

    loadPreset(0);
}

static void handlePushbuttonPress(OneButton *oneButton)
{
    pushbuttons.HandlePress(oneButton->pin());
}

void setup()
{
    // Add initial delay to let power stabilize
    delay(100);  

    D_SerialBegin(9600);
    D_println("*** LCD EQ PEDAL ***");

    // Add delay after serial init
    delay(50);

    SPI.begin();
    delay(50);  // Add delay after SPI init
    
    D_println("SPI initialized...");

    lcd.Begin();
    delay(2000);  // Give LCD more time to initialize

    D_println("LCD initialized...");

    // Group similar inputs together with small delays between groups
    // Footswitches
    footswitch1.setup(FOOTSWITCH_1_PIN, INPUT_PULLUP, true);
    footswitch2.setup(FOOTSWITCH_2_PIN, INPUT_PULLUP, true);
    footswitch3.setup(FOOTSWITCH_3_PIN, INPUT_PULLUP, true);
    delay(50);

    // Set press threshold for all footswitches
    footswitch1.setPressMs(LONG_PRESS_THRESHOLD);
    footswitch2.setPressMs(LONG_PRESS_THRESHOLD);
    footswitch3.setPressMs(LONG_PRESS_THRESHOLD);
    delay(50);

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
    delay(50);

    // Setup other buttons
    ampSwitchButton.setup(AMP_SWITCH_BUTTON_PIN, INPUT_PULLUP, true);
    loop1Button.setup(LOOP1_BUTTON_PIN, INPUT_PULLUP, true);
    loop2Button.setup(LOOP2_BUTTON_PIN, INPUT_PULLUP, true);
    loop3Button.setup(LOOP3_BUTTON_PIN, INPUT_PULLUP, true);
    loop4Button.setup(LOOP4_BUTTON_PIN, INPUT_PULLUP, true);
    delay(50);

    // Attach callbacks for other buttons
    ampSwitchButton.attachClick(handlePushbuttonPress, &ampSwitchButton);
    loop1Button.attachClick(handlePushbuttonPress, &loop1Button);
    loop2Button.attachClick(handlePushbuttonPress, &loop2Button);
    loop3Button.attachClick(handlePushbuttonPress, &loop3Button);
    loop4Button.attachClick(handlePushbuttonPress, &loop4Button);
    delay(50);

    // Load preset with increased delay
    delay(1500);
    loadPreset(0);
    delay(1500);
}

const int cooldownLimit = 100; // Number of loops to skip after stability detected
int cooldownCounter = 0;

void loop()
{
    if (cooldownCounter == 0)
    {
        auto analogPotValues = analogPots.Read();
        auto pushbuttonValues = pushbuttons.Read();

        auto preset = editTracker.TrackChanges(analogPotValues, pushbuttonValues);

        if (preset.PresetChanged || forceApply == true)
        {
            cooldownCounter = 0;

            relays.Toggle(preset);
            lcd.Draw(preset, banks.GetCurrentBank());
            vactrols.ApplyPreset(preset);
            pushbuttons.ApplyPreset(preset);

            relays.UnBypass();

            forceApply = false;
        }
        else
        {
            cooldownCounter = cooldownLimit;
        }

        analogPots.Tick();
        ampSwitchButton.tick();
        loop1Button.tick();
        loop2Button.tick();
        loop3Button.tick();
        loop4Button.tick();
    }
    else
    {
        cooldownCounter--;
    }

    footswitch1.tick();
    footswitch2.tick();
    footswitch3.tick();
}
