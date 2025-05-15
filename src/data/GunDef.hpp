#ifndef GUN_DEF
#define GUN_DEF

#include <iostream>

struct GunDef {
	int id;
	std::string name;
	int damage;
	int range;
	GunDef(const int& id, const std::string& name, const int& damage, const int& range) : id(id), name(name), damage(damage), range(range) {}
};

#endif // !GUN_DEF
