#include <Arduino.h>

#include "VactrolControlValue.h"

class ProximityLookup
{
public:
	ProximityLookup();

	bool AddEntry(int key, VactrolControlValue value);
	VactrolControlValue *FindClosest(int searchKey);

private:
	struct LookupEntry
	{
		int key;
		VactrolControlValue value;
	};

	// Maximum size for the lookup table
	static const int MAX_ENTRIES = 65792;
	LookupEntry lookupTable[MAX_ENTRIES];
	int currentSize;

	int binarySearchClosest(int searchKey);
};
