#ifndef GUN
#define GUN

#include "Weapon.hpp"
#include "Equipment.hpp"
#include "Chip.hpp"

class Gun :public Weapon, public Equipment {
	Chip chips[3];
	float Use() override;
	void TrySetChip(Chip chip);
};

#endif // !GUN
