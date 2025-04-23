#ifndef WEAPON
#define WEAPON

#include "Object.hpp"

class Weapon : public Object {
	int distance;
	float damage;
	virtual float Use() = 0;
};

#endif // !WEAPON
