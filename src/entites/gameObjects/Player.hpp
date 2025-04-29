#ifndef PLAYER
#define PLAYER

#include "Sprite.hpp"
#include "entites/items/Gun.hpp"
#include "entites/items/Armor.hpp"
#include "entites/items/Artifact.hpp"

class Player : public Sprite {
	int damage;
	int armor;
	int maxMana;
	int mana;

	Gun guns[2];
	Artifact artifacts[2];
	Armor armor;

	void Drop() override = 0;
	void Death() override;
	void Move(float delta) override;
	void TakeDamage(int damage) override;
	void DealDamage(std::unique_ptr<GameObject> target) override;
};

#endif // !PLAYER
