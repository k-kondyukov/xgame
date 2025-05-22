#ifndef CHIP_SLOTS
#define CHIP_SLOTS

#include "Chip.hpp"

class ChipSlots {
	Chip chips[3];
	void TrySetChip(Chip chip);
};
#endif // !CHIP_SLOTS
