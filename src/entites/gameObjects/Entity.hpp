#ifndef ENTITY
#define ENTITY

#include "Sprite.hpp"

class Entity : public Sprite {
	virtual void Move(float delta) override;
	void TakeDamage(int damage) override;
	void DealDamage(std::unique_ptr<GameObject> target) override;
	void Drop() override;
};

#endif // !ENTITY
