#ifndef WEAPON
#define WEAPON

#include "Object.hpp"

class Weapon : public Object {
	bool isMelee;
	int damage;
};

#endif // !WEAPON
