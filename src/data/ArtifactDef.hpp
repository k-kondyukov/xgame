#ifndef ARTIFACT_DEF
#define ARTIFACT_DEF

#include <iostream>

struct ArtifactDef {
	int id;
	std::string name;
	int manacost;
	int range;

	ArtifactDef(const int& id, const std::string& name, const int& manacost, const int& range) : id(id), name(name), manacost(manacost), range(range) {}
};

#endif // !ARTIFACT_DEF