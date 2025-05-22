#include "Resources.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture Resources::wallsTexture;
sf::Texture Resources::floorTexture;
sf::Texture Resources::shaderTexture;

void Resources::init() {
    if (!wallsTexture.loadFromFile("sprites/walls.png")) {
        std::cerr << "Ошибка загрузки текстуры walls.png" << std::endl;
        exit(1);
    }

    if (!floorTexture.loadFromFile("sprites/floor.png")) {
        std::cerr << "Ошибка загрузки текстуры floor.png" << std::endl;
        exit(1);
    }

    if (!shaderTexture.loadFromFile("sprites/shader.png")) {
        std::cerr << "Ошибка загрузки текстуры shader.png" << std::endl;
        exit(1);
    }
}