#ifndef DRAWABLE
#define DRAWABLE

#include <iostream>
#include "SFML/Graphics.hpp"

class Drawable {
	std::string name;
	std::unique_ptr<sf::Texture> texture;
	int id;
};

#endif // !DRAWABLE
