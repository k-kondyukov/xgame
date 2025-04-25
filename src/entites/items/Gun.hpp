#ifndef GUN
#define GUN

#include "Weapon.hpp"
#include "Equipment.hpp"
#include "ChipSlots.hpp"

class Gun :public Weapon, public Equipment, public ChipSlots {
	float Use() override;
};

#endif // !GUN
