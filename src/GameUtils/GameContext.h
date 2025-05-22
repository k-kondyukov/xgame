#pragma once

#include <SFML/Graphics.hpp>


struct PlayerContext{

};

struct GameContext {
    sf::RenderWindow &window;
    PlayerContext playerContext;

    explicit GameContext(sf::RenderWindow &window): window(window) {};
    void loadSave(std::string path){
        //toDo: реализовать загрузку
    }


};