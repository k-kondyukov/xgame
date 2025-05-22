#pragma once

#include <iostream>
#include "../level/Level.hpp"

#include "GameContext.h"
#include "ResourceManager.h"

using Coord = sf::Vector2i;

class GameView {
    int visibleHeight = 20;
    int visibleWidth = 20;
    Coord mapPointOfView{0, 0};

    std::vector<std::vector<std::vector<ID>>> drawableField{};
    //toDo: Это фактически слои. Сейчас они работают по-тупому, и порядок слоёв там такой, в каком их кладут.
    // Это Неудобно, т.к. нам может захотеться рисовать что-то между двумя слоями, которые у нас уже есть.
    // Пока реализованы только стены-пол-игрок, однако, это не роляет.
    // Позднее их стоит передалать в OrderedSet. (Ya_ntar)

public:
    explicit GameView(int visibleHeight, int visibleWidth) : visibleHeight(visibleHeight),
                                                             visibleWidth(visibleWidth) {};

    void deleteImage(Coord where, ID what) {
        int numberOfLayer = -1;
        auto &layer = drawableField[where.x][where.y];
        for (int i = 0; i < layer.size(); i++) {
            if (layer[i] == what) {
                numberOfLayer = i;
            }
        }
        if (numberOfLayer == -1) {
            throw std::runtime_error("Failed to delete object " + what + " from View in coords: "
                                     + std::to_string(where.x) + " , " + std::to_string(where.y));
        }
    }
    void addImage(Coord where, ID what) {
        drawableField[where.x][where.y].push_back(what);
    }

};


class Game {
    int levelHeight;
    int levelWidth;
    sf::Image icon;
    sf::RenderWindow window{sf::VideoMode({800, 800}),
                            "ExpeditionGame", sf::Style::Default};
    GameView view;
    ResourceManager textures;
    GameContext context{window};


private:
    void loadResources() {


    }


public:
    Game(int levelWidth = 50, int levelHeight = 50, int visibleWidth = 20, int visibleHeight = 20) :
            levelHeight(levelHeight), levelWidth(levelWidth),
            view(levelWidth, levelHeight) {
        if (icon.loadFromFile("assets/gameIcon.jpg")) {
            window.setIcon(icon);
        }
        loadResources();;
    }

    int run() {

        while (window.isOpen()) {
            while (const std::optional _event = window.pollEvent()) {
                if (_event->is<sf::Event::Closed>()) {
                    window.close();
                }

            }
            window.clear();

            window.display();
        }
        return 0;
    }


};