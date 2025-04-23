#ifndef SPRITE
#define SPRITE

#include <iostream>
#include "GameObject.hpp"
#include "data/SPDef.hpp"
#include "data/SpMap.hpp"
#include "level/Level.hpp"
#include "SFML/Graphics.hpp"

class Sprite:public GameObject {
	SpDef spDef;
	SpMap spMap;
	std::unique_ptr<Level> level;

	void Move(float delta)
	bool checkColission(sf::Vector2f position);
};

#endif // !SPRITE
