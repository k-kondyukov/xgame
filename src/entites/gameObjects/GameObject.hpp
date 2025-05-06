#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "SFML/Graphics.hpp"
#include "View.hpp"
#include "../Drawable.hpp"
#include "Animator.hpp"

class GameObject : public View, public Drawable {
protected:
	int hp;
	int max_hp;
	sf::Vector2f position;
	Animator animator;

	int damage;
	int armor;

	int strength;
	int dexterity;
	int intelegnce;

	int maxArmor;
	int maxStrength;
	int maxDexterity;
	int maxIntelegnce;

public:
	virtual void Drop();
	virtual void Death();
};

#endif // !GAME_OBJECT
