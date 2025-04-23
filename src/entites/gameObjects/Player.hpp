#ifndef PLAYER
#define PLAYER

#include "Sprite.hpp"

class Player : public Sprite {
	void Drop() override = 0;
	void Death() override;
	void Move(float delta) override;
	void TakeDamage() override;
	int DealDamage() override;
};

#endif // !PLAYER
