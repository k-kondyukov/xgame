#pragma once

#include <iostream>
#include "../level/Level.hpp"

#include "GameContext.h"
#include "ResourceManager.h"


class Game {
    sf::Image icon;
    sf::RenderWindow window{sf::VideoMode({800, 800}),
                            "ExpeditionGame", sf::Style::Default};
    GameContext context{window};
    ResourceManager itemManager;

private:
    void loadResources() {


    }


public:
    Game() {
        if (icon.loadFromFile("assets/gameIcon.jpg")) {
            window.setIcon(icon);
        }
        loadResources();
    }

    int run() {

        while (window.isOpen()) {
            while (const std::optional _event = window.pollEvent()) {
                if (_event->is<sf::Event::Closed>()){
                    window.close();
                }

            }
            window.clear();

            window.display();
        }
        return 0;
    }


};