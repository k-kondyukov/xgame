#ifndef GAME
#define GAME

#include <iostream>
#include "level/Level.hpp"
#include "entites/controllers/AIController.hpp"
#include "entites/controllers/PlayerController.hpp"

class Game
{
	Level level;
	AIController AIController;
	PlayerController PlayerController;
};

#endif // !GAME
