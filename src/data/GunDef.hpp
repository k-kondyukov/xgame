#ifndef GUN_DEF
#define GUN_DEF

#include <iostream>

struct GunDef {
	int id;
	std::string name;
	int damage;

	GunDef(const int& id, const std::string& name, const int& damage, const bool& isMelee) : id(id), name(name), damage(damage), isMelee(isMelee) {}
};

#endif // !GUN_DEF
