#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "TextureManager.h"

//static const int TILE_SIZE = 64;
using Coord = sf::Vector2i;

class CoordinateView : public sf::Drawable {

    int visibleHeight;
    int visibleWidth;
    Coord mapPointOfView{0, 0};
    float tileSize = 64.f;

    std::vector<std::vector<std::vector<ID>>>
            drawableField;

    const TextureManager &textures;

public:
    explicit CoordinateView(int visibleHeight, int visibleWidth, int realHeight, int realWidth,
                            const TextureManager &textures)
            : visibleHeight(visibleHeight),
              visibleWidth(visibleWidth),
              textures(textures) {
        drawableField.resize(realHeight, std::vector<std::vector<ID >>(realWidth));
    }
    void clear(){
        for (auto &row: drawableField) {
            for (auto &layers: row) {
                layers.clear();
            }
        }

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

        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                for (const ID &tileID: drawableField[y][x]) {
                    sf::Sprite sprite(textures.get(tileID)->get());

                    sf::FloatRect textureRect = sprite.getLocalBounds();
                    sprite.setScale({tileSize / textureRect.size.x,
                                     tileSize / textureRect.size.y});
                    float xF = (float) (x - mapPointOfView.x) * tileSize;
                    float yF = (float) (y - mapPointOfView.y) * tileSize;


                    sprite.setPosition({xF, yF});
                    target.draw(sprite, states);
                }
            }
        }
    }
};