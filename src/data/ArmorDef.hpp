#ifndef ARMOR_DEF
#define ARMOR_DEF

#include <iostream>

struct ArmorDef {
	int id;
	std::string name;
	int armor;
	ArmorDef(const int& id, const std::string& name, const int& armor) : id(id), name(name), armor(armor) {}
};

#endif // !ARMOR_DEF