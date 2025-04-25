#ifndef ARTIFACT
#define ARTIFACT

#include "Weapon.hpp"
#include "Equipment.hpp"
#include "ChipSlots.hpp"

class Artifact: public Weapon, public Equipment, public ChipSlots {
	int manacost;
	float Use() override;
};

#endif