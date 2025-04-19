#ifndef RESOURCES
#define RESOURCES

#include <SFML/Graphics/Texture.hpp>

constexpr int TEXTURE_SIZE = 16, ROW_WALL_TEXT_COUNT = 6, ROW_SHADER_TEXT_COUNT = 6, 
ROW_FLOOR_TEXT_COUNT = 3, EMPTY_CELL_CODE = -1;

class Resources
{
public:
	static sf::Texture wallTextures;
	static sf::Texture floorTextures;
	static sf::Texture shaderWallTexture;
};

#endif // !RESOURCES
