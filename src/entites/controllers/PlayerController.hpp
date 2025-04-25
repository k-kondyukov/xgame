#ifndef PLAYER_CONTROLLER
#define PLAYER_CONTROLLER

#include <iostream>
#include "Controller.hpp"

class PlayerController : public Controller{
	virtual bool CheckCollision(sf::Vector2f position) override;
	virtual void Init(std::vector<SpMap>) override;
class PlayerController {
	void Init(std::vector<SpMap>);
	std::unique_ptr<View> GetView();
	Player GetPlayer();
};

#endif // !PLAYER_CONTROLLER
