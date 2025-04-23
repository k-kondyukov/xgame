#ifndef ENTITY
#define ENTITY

#include "Sprite.hpp"

class Entity : public Sprite {
	int damage;
	virtual void Move(float delta) override;
	virtual void TakeDamage(int damage);
	virtual void DealDamage();
	void Drop() override;
};

#endif // !ENTITY
