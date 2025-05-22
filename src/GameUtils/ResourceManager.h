#pragma once

#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include <map>


using ID = std::string;


struct Resource {
    ID id;
    sf::Texture texture;

    Resource(ID id, const std::string &texturePath) :
            id(std::move(id)) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
    }


};


class ResourceManager {
    std::map<ID, std::shared_ptr<Resource>> database;

public:
    [[nodiscard]] const std::shared_ptr<Resource> &getResource(const ID &id) const {
        return database.at(id);
    }

    [[nodiscard]] const std::map<ID, std::shared_ptr<Resource>> &getResources() const {
        return database;
    }

    void addResource(const ID &id, const std::string &texturePath) {
        if (database.contains(id)) {
            throw std::runtime_error("Id was already loaded: " + id);
        }
        database.emplace(id, std::make_shared<Resource>(id, texturePath));
    }

};