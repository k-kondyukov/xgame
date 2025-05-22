#ifndef DISC_DEF
#define DISC_DEF

#include <iostream>

struct DiscDef {
	int id;
	std::string description;

	DiscDef(const int& id, const std::string& description) : id(id), description(description) {}

};

#endif // !DISC_DEF
