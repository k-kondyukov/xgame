#ifndef WEAPON
#define WEAPON

#include "Object.hpp"

class Weapon : public Object {
	int distance;
	int damage;

	int GetDamage();
	int GetDistance();
};

#endif // !WEAPON
