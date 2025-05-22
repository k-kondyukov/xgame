#ifndef VIEW
#define VIEW

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"

class View : public sf::Drawable
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
};

#endif // !VIEW
