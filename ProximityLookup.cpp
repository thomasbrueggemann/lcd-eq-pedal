#include "ProximityLookup.h"

ProximityLookup::ProximityLookup() : currentSize(0) {}

// add an entry to the lookup table, keeping it sorted
bool ProximityLookup::AddEntry(int key, VactrolControlValue value)
{
	if (currentSize >= MAX_ENTRIES)
	{
		return false; // Table full
	}

	// insert key in the sorted order
	int i;
	for (i = currentSize - 1; (i >= 0 && lookupTable[i].key > key); i--)
	{
		lookupTable[i + 1] = lookupTable[i]; // Shift elements to the right
	}

	// insert the new entry
	lookupTable[i + 1].key = key;
	lookupTable[i + 1].value = value;
	currentSize++;

	return true;
}

// Find the closest entry for the given key
VactrolControlValue *ProximityLookup::FindClosest(int searchKey)
{
	if (currentSize == 0)
	{
		return nullptr; // no entries in the table
	}

	int closestIndex = binarySearchClosest(searchKey);
	return &lookupTable[closestIndex].value;
}

// Utility function to perform binary search for the closest key
int ProximityLookup::binarySearchClosest(int searchKey)
{
	int low = 0;
	int high = currentSize - 1;

	if (searchKey <= lookupTable[low].key)
		return low;

	if (searchKey >= lookupTable[high].key)
		return high;

	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (lookupTable[mid].key == searchKey)
		{
			return mid; // exact match
		}
		else if (lookupTable[mid].key < searchKey)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	// at this point, low > high and the key is between lookupTable[high] and lookupTable[low]
	if (low >= currentSize)
		return high; // searchKey is larger than all keys, return last entry

	if (high < 0)
		return low; // searchKey is smaller than all keys, return first entry

	// find the closest of the two (lookupTable[high] or lookupTable[low])
	if (abs(lookupTable[low].key - searchKey) < abs(lookupTable[high].key - searchKey))
	{
		return low;
	}
	else
	{
		return high;
	}
}