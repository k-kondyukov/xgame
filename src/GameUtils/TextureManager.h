#pragma once

#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include <map>


using ID = std::string;


struct TextureWrapper {
private:
    ID id;
    sf::Texture texture;
public:
    TextureWrapper(ID id, const std::string &texturePath) :
            id(std::move(id)) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
    }
    const sf::Texture& get() const{
        return texture;
    }

};


class TextureManager {
    std::map<ID, std::shared_ptr<TextureWrapper>> database;

public:
    [[nodiscard]] const std::shared_ptr<TextureWrapper> &get(const ID &id) const {
        return database.at(id);
    }

    [[nodiscard]] const std::map<ID, std::shared_ptr<TextureWrapper>> &getAll() const {
        return database;
    }

    void addResource(const ID &id, const std::string &texturePath) {
        if (database.contains(id)) {
            throw std::runtime_error("Id was already loaded: " + id);
        }
        database.emplace(id, std::make_shared<TextureWrapper>(id, texturePath));
    }

};