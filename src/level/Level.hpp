#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "data/SpMap.hpp"
#include "Map.hpp"
#include "Observer.hpp"

class Level : public Observable
{
public:
	int LevelCounter;
	Map map;
	sf::Vector2i endLevelPos;

	Level();

	void Save();
	void Load();
	void GetMap();
};

#endif // !LEVEL_HPP