#ifndef PLAYER_CONTROLLER
#define PLAYER_CONTROLLER

#include <iostream>
#include "Controller.hpp"

class PlayerController : public Controller{
	std::unique_ptr<View> GetView();
	virtual bool CheckCollision(sf::Vector2f position) override;
	virtual void Init(std::vector<SpMap>) override;
};

#endif // !PLAYER_CONTROLLER
