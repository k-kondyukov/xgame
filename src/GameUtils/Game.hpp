#pragma once

#include <iostream>
#include "../level/Level.hpp"

#include "GameContext.h"
#include "TextureManager.h"
#include "../level/Map.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <string>

static const int TILE_SIZE = 64;
using Coord = sf::Vector2i;

class GameView : public sf::Drawable {
    int visibleHeight;
    int visibleWidth;
    Coord mapPointOfView{0, 0};
    float tileSize = TILE_SIZE;

    // Теперь правильно: [y][x][layers]
    std::vector<std::vector<std::vector<ID>>> drawableField;

    const TextureManager& textures;

public:
    explicit GameView(int visibleHeight, int visibleWidth, int realHeight, int realWidth,
                      const TextureManager& textures)
            : visibleHeight(visibleHeight),
              visibleWidth(visibleWidth),
              textures(textures)
    {
        // Инициализация с правильным порядком: сначала строки (y), затем столбцы (x)
        drawableField.resize(realHeight, std::vector<std::vector<ID>>(realWidth));
    }

    void deleteImage(Coord where, ID what) {
        if (where.y < 0 || where.y >= drawableField.size() ||
            where.x < 0 || where.x >= drawableField[where.y].size()) {
            throw std::out_of_range("Coordinates out of bounds");
        }

        auto& layers = drawableField[where.y][where.x];
        auto it = std::find(layers.begin(), layers.end(), what);

        if (it == layers.end()) {
            throw std::runtime_error("Object " + (what) +
                                     " not found at coordinates: " +
                                     std::to_string(where.x) + ", " +
                                     std::to_string(where.y));
        }

        layers.erase(it);
    }

    void addImage(Coord where, ID what) {
        if (where.y < 0 || where.y >= drawableField.size() ||
            where.x < 0 || where.x >= drawableField[where.y].size()) {
            throw std::out_of_range("Coordinates out of bounds");
        }

        drawableField[where.y][where.x].push_back(what);
    }

    void setViewPosition(Coord newPosition) {
        mapPointOfView = newPosition;
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        int startY = std::max(0, mapPointOfView.y);
        int startX = std::max(0, mapPointOfView.x);
        int endY = std::min((int)drawableField.size(), mapPointOfView.y + visibleHeight);
        int endX = std::min((int)drawableField[0].size(), mapPointOfView.x + visibleWidth);

        // Правильный порядок: сначала y (строки), затем x (столбцы)
        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                for (const ID& tileID : drawableField[y][x]) {
                    sf::Sprite sprite(textures.get(tileID)->get());

                    sf::FloatRect textureRect = sprite.getLocalBounds();
                    sprite.setScale({TILE_SIZE / textureRect.size.x,
                                     TILE_SIZE / textureRect.size.y});
                    float xF = (float) (x - mapPointOfView.x) * tileSize;
                    float yF = (float) (y - mapPointOfView.y) * tileSize;


                    sprite.setPosition({xF, yF});
                    target.draw(sprite, states);
                }
            }
        }
    }
};
class Game {
    int levelHeight;
    int levelWidth;
    sf::Image icon;
    sf::RenderWindow window{sf::VideoMode({800, 800}),
                            "Project X", sf::Style::Default};
    GameView view;
    TextureManager textures;
    GameContext context{window};


private:
    void loadResources() {
        textures.addResource("floor", "assets/tiles/floor.png");
        textures.addResource("wall", "assets/tiles/wall.png");
        textures.addResource("solid wall", "assets/tiles/wall_solid.png");
    }


public:
    explicit Game(int levelWidth = 20, int levelHeight = 20, int visibleWidth = 20, int visibleHeight = 20) :
            levelHeight(levelHeight), levelWidth(levelWidth),
            view(visibleWidth, visibleHeight, levelWidth, levelHeight, textures) {
        if (icon.loadFromFile("assets/gameIcon.jpg")) {
            window.setIcon(icon);
        }
        loadResources();



    }

    int run() {

        Map map(levelWidth, levelHeight);
        map.show();
        auto &field = map.getField();

        for (int y = 0; y < levelHeight; ++y) {
            for (int x = 0; x < levelWidth; ++x) {
                auto &cell = field[y][x];
                if (cell.floor == Floor::DefaultFloor){
                    view.addImage({x, y}, "floor");
                }

                if (cell.wall.orientation == WallOrientation::Front && cell.wall.type == WallType::Stone){
                    view.addImage({x, y}, "wall");
                } else if (cell.wall.orientation == WallOrientation::Full && cell.wall.type == WallType::Stone){
                    view.addImage({x, y}, "solid wall");
                }
            }
        }

        while (window.isOpen()) {
            while (const std::optional _event = window.pollEvent()) {
                if (_event->is<sf::Event::Closed>()) {
                    window.close();
                }

            }

            window.clear();
            window.draw(view);
            window.display();
        }
        return 0;
    }


};