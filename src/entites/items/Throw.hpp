#ifndef THROW
#define THROW

#include "Weapon.hpp"

class Throw : public Weapon {
	virtual float Use() override;
};

#endif THROW