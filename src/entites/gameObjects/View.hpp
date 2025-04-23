#ifndef VIEW
#define VIEW

#include "SFML/Graphics.hpp"

class View {
	virtual void Draw(sf::RenderWindow*) = 0;
	virtual void Update(float deltaTime) = 0;
};

#endif // !VIEW
