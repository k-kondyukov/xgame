#ifndef AI_CONTROLLER
#define AI_CONTROLLER

#include <iostream>
#include "Controller.hpp"

class AIController : public Controller{
	std::vector<std::unique_ptr<View>> GetView();
	virtual bool CheckCollision(sf::Vector2f position) override;
	virtual void Init(std::vector<SpMap>) override;
};

#endif // !AI_CONTROLLER
