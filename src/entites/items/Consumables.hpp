#ifndef CONSUMABLES
#define CONSUMABLES

#include "Effects.hpp"
#include "entites/gameObjects/Player.hpp"

class Consumables {
	int usingTime;
	int currentTime;

	bool Update();

	void Use(Player& player);
};

#endif