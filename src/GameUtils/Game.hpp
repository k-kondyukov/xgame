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

    const TextureManager &textures;

public:
    explicit GameView(int visibleHeight, int visibleWidth, int realHeight, int realWidth,
                      const TextureManager &textures)
            : visibleHeight(visibleHeight),
              visibleWidth(visibleWidth),
              textures(textures) {
        // Инициализация с правильным порядком: сначала строки (y), затем столбцы (x)
        drawableField.resize(realHeight, std::vector<std::vector<ID>>(realWidth));
    }

    void deleteImage(Coord where, ID what) {
        if (where.y < 0 || where.y >= drawableField.size() ||
            where.x < 0 || where.x >= drawableField[where.y].size()) {
            throw std::out_of_range("Coordinates out of bounds");
        }

        auto &layers = drawableField[where.y][where.x];
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
        mapPointOfView.x = std::min(newPosition.x, (int) drawableField[0].size() - visibleWidth - 1);
        mapPointOfView.y = std::min(newPosition.y, (int) drawableField.size() - visibleWidth - 1);
    }
    void setCenteredViewPosition(Coord newPosition) {
        int x = newPosition.x - visibleWidth / 2;
        int y = newPosition.y - visibleHeight / 2;
        setViewPosition({x, y});
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        int startY = std::max(0, mapPointOfView.y);
        int startX = std::max(0, mapPointOfView.x);
        int endY = std::min((int) drawableField.size(), mapPointOfView.y + visibleHeight);
        int endX = std::min((int) drawableField[0].size(), mapPointOfView.x + visibleWidth);

        // Правильный порядок: сначала y (строки), затем x (столбцы)
        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                for (const ID &tileID: drawableField[y][x]) {
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

class Player {
    Coord place;
    const Field &field;
    GameView &view;

    void deleteView() { view.deleteImage(place, "player"); }
    void addView() { view.addImage(place, "player"); }
    void updatePov(){
        view.setCenteredViewPosition(place);
    }

    bool moveIfPossible(Coord newPlace) {
        if (newPlace.x < 0 || newPlace.y < 0 ||
            newPlace.x >= field.width || newPlace.y >= field.height ||
            !field[newPlace.y][newPlace.x].passable()) {
            return false;
        }

        deleteView();
        place = newPlace;
        addView();
        updatePov();
        return true;
    }

public:
    Player(Coord place, const Field &field, GameView &view):
            place(place), field(field), view(view) {}

    Coord getPlace() const { return place; }

    void up() {
        moveIfPossible({place.x, place.y - 1});
    }

    void down() {
        moveIfPossible({place.x, place.y + 1});
    }

    void left() {
        moveIfPossible({place.x - 1, place.y});
    }

    void right() {
        moveIfPossible({place.x + 1, place.y});
    }
};

class Game {
    int levelHeight;
    int levelWidth;

    sf::Image icon;
    sf::RenderWindow window{sf::VideoMode({800, 800}),
                            "Project X", sf::Style::Default};
    int visibleWidth = (int) window.getSize().x / TILE_SIZE;
    int visibleHeight = (int) window.getSize().y / TILE_SIZE;
    GameView view;
    std::optional<Player> player;
    TextureManager textures;
    GameContext context{window};


private:
    void loadResources() {
        textures.addResource("floor", "assets/tiles/floor.png");
        textures.addResource("wall", "assets/tiles/wall.png");
        textures.addResource("solid wall", "assets/tiles/wall_solid.png");
        textures.addResource("background", "assets/background.jpg");
        textures.addResource("player", "assets/characters/player.png");
    }


public:
    explicit Game(int levelWidth = 50, int levelHeight = 50) :
            levelHeight(levelHeight), levelWidth(levelWidth),
            view(visibleWidth, visibleHeight, levelWidth, levelHeight, textures) {
        if (icon.loadFromFile("assets/gameIcon.jpg")) {
            window.setIcon(icon);
        }
        loadResources();

    }



    int run() {
       /* sf::Sprite backgroundSprite(textures.get("background")->get());
        backgroundSprite.setPosition({0, 0});*/

        Map map(levelWidth, levelHeight, 20);
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
        Player pl({rooms.first.x + 1, rooms.first.y + 1}, map.getField(), view);
        player.emplace(pl);

        view.setCenteredViewPosition(player->getPlace());
        view.addImage(player->getPlace(), "player");


        while (window.isOpen()) {

            processEvents();
            while (const std::optional _event = window.pollEvent()) {
                if (_event->is<sf::Event::Closed>()) {
                    window.close();
                }

            }
            render();
        }
        return 0;
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