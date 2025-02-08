#include "PresetStore.h"
#include <EEPROM.h>

// Magic byte to identify initialized presets
#define PRESET_MAGIC_BYTE 0xAA
#define EEPROM_SIZE 4096

Preset getDefaultPreset() {
    Preset preset;
    preset.Bass = 512;
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
    return (bank * NUM_PRESETS_PER_BANK + preset) * (NUM_BYTES_PER_PRESET + 1); // +1 for magic byte
}

void PresetStore::Write(int bank, int preset, Preset &payload) {
    if (!isValidBankPreset(bank, preset)) {
        return;
    }

    int startingAddress = getStartingAddress(bank, preset);
    
    if (!isValidAddress(startingAddress, NUM_BYTES_PER_PRESET + 1)) { // +1 for magic byte
        return;
    }

    // First write the magic byte
    EEPROM.write(startingAddress, PRESET_MAGIC_BYTE);
    
    // Then write the preset data starting at the next address
    EEPROM.put(startingAddress + 1, payload);
    
    // Update cache if this is for the current bank
    if (bank == currentBank) {
        BankPresets[preset] = payload;
    }

    // Small delay to let EEPROM write complete
    delay(5);
}

Preset PresetStore::Read(int preset) {
    if (!isValidBankPreset(currentBank, preset)) {
        return getDefaultPreset();
    }
    
    // Return from cache
    return BankPresets[preset];
}

void PresetStore::PreloadBank(int bank) {
    if (!isValidBankPreset(bank, 0)) { // Check if bank number is valid
        return;
    }

    currentBank = bank;
    
    for (int i = 0; i < NUM_PRESETS_PER_BANK; i++) {
        int startingAddress = getStartingAddress(bank, i);
        
        if (!isValidAddress(startingAddress, NUM_BYTES_PER_PRESET + 1)) {
            BankPresets[i] = getDefaultPreset();
            continue;
        }

        // Read and verify magic byte
        byte magicByte = EEPROM.read(startingAddress);
        
        if (magicByte != PRESET_MAGIC_BYTE) {
            D_print(F("Invalid magic byte at address "));
            D_print(startingAddress);
            D_print(F(" expected 0xAA got 0x"));
            D_println(magicByte, HEX);
            BankPresets[i] = getDefaultPreset();
            continue;
        }

        // Read the preset data from the address after the magic byte
        EEPROM.get(startingAddress + 1, BankPresets[i]);
        
        // Small delay between reads
        delay(5);
    }
}

// Optional: Add this method to help debug EEPROM contents
void PresetStore::DebugDump() {
    for (int bank = 0; bank < 4; bank++) {  // Assuming 4 banks
        for (int preset = 0; preset < NUM_PRESETS_PER_BANK; preset++) {
            int addr = getStartingAddress(bank, preset);
            byte magic = EEPROM.read(addr);
            D_print(F("Bank "));
            D_print(bank);
            D_print(F(" Preset "));
            D_print(preset);
            D_print(F(" @ "));
            D_print(addr);
            D_print(F(": Magic=0x"));
            D_println(magic, HEX);
        }
    }
}