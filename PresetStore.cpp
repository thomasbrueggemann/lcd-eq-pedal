#include "PresetStore.h"
#include <EEPROM.h>

// Magic byte to identify initialized presets
#define PRESET_MAGIC_BYTE 0xAA
#define EEPROM_SIZE 4096

Preset getDefaultPreset() {
    Preset preset;
    preset.Bass = 512;      // Center position
    preset.Middle = 512;
    preset.Treble = 512;
    preset.Volume = 512;
    preset.AmpSwitch = false;
    preset.Loop1 = false;
    preset.Loop2 = false;
    preset.Loop3 = false;
    preset.Loop4 = false;
    return preset;
}

bool PresetStore::isValidAddress(int address, int size) {
    return (address >= 0) && ((address + size) < EEPROM_SIZE);
}

bool PresetStore::isValidBankPreset(int bank, int preset) {
    return (bank >= 0) && (preset >= 0) && (preset < NUM_PRESETS_PER_BANK);
}

int PresetStore::getStartingAddress(int bank, int preset) {
    return (bank * NUM_PRESETS_PER_BANK + preset) * NUM_BYTES_PER_PRESET;
}

void PresetStore::Write(int bank, int preset, Preset &payload) {
    if (!isValidBankPreset(bank, preset)) {
        return;  // Silent fail for invalid bank/preset
    }

    int startingAddress = getStartingAddress(bank, preset);
    
    if (!isValidAddress(startingAddress, NUM_BYTES_PER_PRESET)) {
        return;  // Silent fail for invalid address
    }

    // Write magic byte first
    EEPROM.write(startingAddress, PRESET_MAGIC_BYTE);
    
    // Write preset data after magic byte
    EEPROM.put(startingAddress + 1, payload);
    
    // Update cache
    if (bank == currentBank) {
        BankPresets[preset] = payload;
    }
}

Preset PresetStore::Read(int preset) {
    if (!isValidBankPreset(currentBank, preset)) {
        return getDefaultPreset();
    }
    
    return BankPresets[preset];
}

void PresetStore::PreloadBank(int bank) {
    if (bank == currentBank) {
        return;  // Bank already loaded
    }

    currentBank = bank;
    
    for (int i = 0; i < NUM_PRESETS_PER_BANK; i++) {
        int startingAddress = getStartingAddress(bank, i);
        
        if (!isValidAddress(startingAddress, NUM_BYTES_PER_PRESET)) {
            BankPresets[i] = getDefaultPreset();
            continue;
        }

        // Check magic byte
        byte magicByte = EEPROM.read(startingAddress);
        if (magicByte != PRESET_MAGIC_BYTE) {
            BankPresets[i] = getDefaultPreset();
            continue;
        }

        // Read actual preset data
        EEPROM.get(startingAddress + 1, BankPresets[i]);
        
        // Add delay between reads to prevent power issues
        delay(50);
    }
}