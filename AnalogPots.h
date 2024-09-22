#ifndef ANALOGPOTS_H
#define ANALOGPOTS_H

#include <Arduino.h>
#include <ResponsiveAnalogRead.h>

#include "AnalogPotValues.h"

class AnalogPots
{
public:
  AnalogPots();
	AnalogPotValues Read();

  void Tick();

private:
  ResponsiveAnalogRead bassPot;
  ResponsiveAnalogRead middlePot;
  ResponsiveAnalogRead treblePot;
  ResponsiveAnalogRead volumePot;

};

#endif // ANALOGPOTS_H