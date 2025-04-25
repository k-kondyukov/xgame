#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include "entites/gameObjects/View.hpp"
#include "entites/gameObjects/GameObject.hpp"
#include "data/SpMap.hpp"
#include "entites/gameObjects/Player.hpp"

class Controller {
	std::vector<std::unique_ptr<View>> GetView();
	std::vector <std::unique_ptr<GameObject>> GetGameObjects();
	Player GetPlayer();
	virtual bool CheckCollision(sf::Vector2f position) = 0;
	virtual void Init(std::vector<SpMap>) = 0;
};

#endif // !CONTROLLER
