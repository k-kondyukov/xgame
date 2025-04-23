#ifndef AI_CONTROLLER
#define AI_CONTROLLER

#include <iostream>
#include "entites/gameObjects/View.hpp"
#include "data/SpMap.hpp"
#include "entites/gameObjects/Player.hpp"

class AIController {
	void Init(std::vector<SpMap>);
	std::vector<std::unique_ptr<View>> GetView();
	Player GetPlayer();
};

#endif // !AI_CONTROLLER
