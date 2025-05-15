#ifndef SPDEF
#define SPDEF

#include <iostream>

struct SpDef
{
	int maxHp;
	int id;
	int damage;
	SpDef(const int& id, const int& maxHp, const int& damage) : maxHp(maxHp), id(id), damage(damage) {}
};

#endif // !SPDEF

