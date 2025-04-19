#ifndef MAP
#define MAP

#include <iostream>
#include <vector>

class Map
{
public:
	int lvlCounter;
	std::vector<std::vector<int>> wall;
	std::vector<std::vector<int>> floor;
	std::vector<std::vector<int>> shader; // это для мха, трещин и тд

	Map();

	void Generate(std::string parametrs);
};

#endif // !MAP
