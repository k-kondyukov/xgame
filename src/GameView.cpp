#include "GameView.hpp"

void GameView::drawMap()
{
	sf::RectangleShape cellShape(sf::Vector2f(TEXTURE_SIZE, TEXTURE_SIZE));

	// floor part
	cellShape.setTexture(&Resources::floorTextures);
	for (int y = 0; y < level.map.floor.size(); y++) {
		for (int x = 0; x < level.map.floor[y].size(); x++) {
			int floorValue = level.map.floor[y][x];

			if (floorValue == EMPTY_CELL_CODE) continue;

			cellShape.setTextureRect(sf::IntRect(sf::Vector2i(floorValue % ROW_FLOOR_TEXT_COUNT, floorValue / ROW_FLOOR_TEXT_COUNT) * TEXTURE_SIZE, 
				sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));
			cellShape.setPosition(sf::Vector2f(TEXTURE_SIZE * x, TEXTURE_SIZE * y));
			window.draw(cellShape);
		}
	}

	// wall part
	cellShape.setTexture(&Resources::wallTextures);
	for (int y = 0; y < level.map.wall.size(); y++) {
		for (int x = 0; x < level.map.wall[y].size(); x++) {
			int wallValue = level.map.wall[y][x];

			if (wallValue == EMPTY_CELL_CODE) continue;

			cellShape.setTextureRect(sf::IntRect(sf::Vector2i(wallValue % ROW_WALL_TEXT_COUNT, wallValue / ROW_WALL_TEXT_COUNT) * TEXTURE_SIZE,
				sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));

			cellShape.setPosition(sf::Vector2f(TEXTURE_SIZE * x, TEXTURE_SIZE * y));
			window.draw(cellShape);
		}
	}

	// shaderPart
	cellShape.setTexture(&Resources::shaderWallTexture);
	for (int y = 0; y < level.map.shader.size(); y++) {
		for (int x = 0; x < level.map.shader[y].size(); x++) {
			int shaderValue = level.map.shader[y][x];

			if (shaderValue == EMPTY_CELL_CODE) continue;

			cellShape.setTextureRect(sf::IntRect(sf::Vector2i(shaderValue % ROW_WALL_TEXT_COUNT, shaderValue / ROW_WALL_TEXT_COUNT) * TEXTURE_SIZE,
				sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));
			cellShape.setPosition(sf::Vector2f(TEXTURE_SIZE * x, TEXTURE_SIZE * y));
			window.draw(cellShape);
		}
	}

	// SpritePart
	for (int i = 0; i < level.views.size(); i++)
	{
		window.draw(*level.views[i].get());
	}
}

void GameView::draw()
{
	drawMap();
}
