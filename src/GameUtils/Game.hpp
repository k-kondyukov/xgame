#pragma once

#include <iostream>
#include "../level/Level.hpp"

#include "TextureManager.h"
#include "../level/Map.hpp"
#include "CoordinateView.h"
#include "MovingObject.h"

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


static const float FRAMES_PER_SECOND = 60.f;

class Game {
    const sf::Time TimePerFrame = sf::seconds(1.f / FRAMES_PER_SECOND);

    int levelHeight;
    int levelWidth;

    sf::Image icon;
    sf::RenderWindow window{sf::VideoMode({800, 800}),
                            "Project X",sf::Style::Titlebar | sf::Style::Close};
    int visibleWidth = (int) window.getSize().x / TILE_SIZE;
    int visibleHeight = (int) window.getSize().y / TILE_SIZE;

    CoordinateView view;
    std::optional<MovingObject> player;
    TextureManager textures;


private:
    void loadResources() {
        textures.addResource("floor", "assets/tiles/floor.png");
        textures.addResource("wall", "assets/tiles/wall.png");
        textures.addResource("solid wall", "assets/tiles/wall_solid.png");
        textures.addResource("player", "assets/characters/player.png");
    }


public:
    explicit Game(int levelWidth = 50, int levelHeight = 50) :
            levelHeight(levelHeight), levelWidth(levelWidth),
            view(visibleHeight, visibleWidth, levelWidth, levelHeight, textures) {
        if (icon.loadFromFile("assets/gameIcon.png")) {
            window.setIcon(icon);
        }
        loadResources();

    }


    int run() {
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        Map map(levelWidth, levelHeight, 20);

        initializeLvl(map);


        while (window.isOpen()) {
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
            }
          
            render();
        }
        return 0;
    }

    void initializeLvl(Map &map) {
        map.show();
        auto &field = map.getField();
        for (int y = 0; y < levelHeight; ++y) {
            for (int x = 0; x < levelWidth; ++x) {
                auto &cell = field[y][x];
                if (cell.floor == Floor::DefaultFloor) {
                    view.addImage({x, y}, "floor");
                }
                if (cell.wall.orientation == WallOrientation::Front && cell.wall.type == WallType::Stone) {
                    view.addImage({x, y}, "wall");
                } else if (cell.wall.orientation == WallOrientation::Full && cell.wall.type == WallType::Stone) {
                    view.addImage({x, y}, "solid wall");
                }
            }
        }


        auto rooms = map.findFurthestRooms();
        MovingObject pl("player", {rooms.first.x + 1, rooms.first.y + 1}, map.getField(), view);
        player.emplace(pl);

        view.setCenteredViewPosition(player->getPlace());
        view.addImage(player->getPlace(), "player");
    }

    void render() {
        window.clear();
        //window.draw(backgroundSprite);
        window.draw(view);
        window.display();
    }

    void processEvents() {
        const auto onClose = [this](const sf::Event::Closed &) {
            window.close();
        };
        const auto onKeyPressed = [this](const sf::Event::KeyPressed &keyPressed) {
            if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            } else {
                handlePlayerInput(keyPressed.code);
            }
        };
        const auto onKeyReleased = [this](const sf::Event::KeyReleased &keyReleased) {
            /*handlePlayerInput(false, keyReleased.code);*/
        };

        window.handleEvents(onClose, onKeyPressed, onKeyReleased);
    }

    void handlePlayerInput(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Key::W)
            player.value().up();
        else if (key == sf::Keyboard::Key::S)
            player.value().down();
        else if (key == sf::Keyboard::Key::A)
            player.value().left();
        else if (key == sf::Keyboard::Key::D)
            player.value().right();
    }


};