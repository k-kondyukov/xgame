#ifndef ARMOR
#define ARMOR

#include "Equipment.hpp"
#include "ChipSlots.hpp"

class Armor : public Equipment, public ChipSlots {
	int armor;
};

#endif // !ARMOR
