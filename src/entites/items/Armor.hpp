#ifndef ARMOR
#define ARMOR

#include "Equipment.hpp"
#include "Effects.hpp"
#include "Chip.hpp"

class Armor : public Equipment, public Effects {
	Chip chips[3];
	void TrySetChip(Chip chip);
};

#endif // !ARMOR
