#ifndef ANALOGPOTS_H
#define ANALOGPOTS_H

#include <Arduino.h>
#include "AnalogPotValues.h"

class AnalogPots
{
public:
	AnalogPotValues Read();

private:
	// Add private members here if needed
};

#endif // ANALOGPOTS_H