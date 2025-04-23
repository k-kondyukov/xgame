#ifndef ARTIFACT
#define ARTIFACT

#include "Effects.hpp"
#include "Weapon.hpp"
#include "Equipment.hpp"
#include "Chip.hpp"

class Artifact: public Effects, public Weapon, public Equipment {
	int manacost;
	float Use() override;
	Chip chips[3];
	void TrySetChip(Chip chip);
};

#endif