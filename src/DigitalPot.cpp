#include "DigitalPot.h"

DigitalPot::DigitalPot(int csPin, byte address)
	: csPin(csPin), address(address)
{
	pinMode(csPin, OUTPUT);
}

void DigitalPot::setValue(int value)
{
	digitalWrite(csPin, LOW);
	SPI.transfer(address);
	SPI.transfer(value);
	digitalWrite(csPin, HIGH);
}