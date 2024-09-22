#ifndef DIGITALPOT_HPP
#define DIGITALPOT_HPP

#include <Arduino.h>
#include <SPI.h>

#define TREBLE_POT_CS 10
#define MID_POT_CS 11
#define BASS_POT_CS 12
#define VOLUME_POT_CS 13

class DigitalPot
{
public:
	DigitalPot(int csPin, byte address);

	void setValue(int value);

private:
	int csPin;
	byte address;
};
;

#endif // DIGITALPOT_HPP