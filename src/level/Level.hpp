#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <vector>
#include <fstream>

#include "SFML/Graphics.hpp"
#include "data/SpMap.hpp"
#include "Map.hpp"
#include "Observer.hpp"
#include "entites/gameObjects/View.hpp"

class Level : public Observable
{
public:
	int LevelCounter;
	Map map;
	sf::Vector2i endLevelPos;
	std::vector<std::unique_ptr<View>> views;
	std::vector<SpMap> spMap;

	Level();

	void Save(const std::string& path);
	void Load(const std::string& path);
	void GetMap();
};

#endif // !LEVEL_HPP