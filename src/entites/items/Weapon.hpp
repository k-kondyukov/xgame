#ifndef WEAPON
#define WEAPON

#include "Object.hpp"

class Weapon : public Object {

	bool isMelee;
	int damage;

	virtual float Use() = 0;

};

#endif // !WEAPON
