#ifndef PLAYER_CONTROLLER
#define PLAYER_CONTROLLER

#include <iostream>
#include "entites/gameObjects/View.hpp"
#include "data/SpMap.hpp"
#include "entites/gameObjects/Player.hpp"

class PlayerController {
	void Init(std::vector<SpMap>);
	std::unique_ptr<View> GetView();
	Player GetPlayer();
};

#endif // !PLAYER_CONTROLLER
