#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "TextureManager.h"
#include "CoordinateView.h"
#include "../level/MapGenerator.h"

class MovingObject {
protected:

    ID id;
    Coord place;
    const Field &field;
    CoordinateView &view;

    void deleteView() { view.deleteImage(place, id); }

    void addView() { view.addImage(place, id); }

    bool moveIfPossible(Coord newPlace) {
        if (newPlace.x < 0 || newPlace.y < 0 ||
            newPlace.x >= field.getWidth() || newPlace.y >= field.getHeight() ||
            !field[newPlace.y][newPlace.x].passable()) {
            return false;
        }

        deleteView();
        place = newPlace;
        addView();
        return true;
    }

    bool moveRundomIfPossible() {

        std::vector<Coord> shuffledDirs = { {place.x, place.y - 1}, {place.x, place.y + 1}, {place.x - 1, place.y}, {place.x + 1, place.y} };

        std::shuffle(shuffledDirs.begin(), shuffledDirs.end(), std::mt19937(std::random_device()()));

        for (Coord newPlace : shuffledDirs) {
            if (moveIfPossible(newPlace)) {
                return true;
            }
        }

        return false;
    }

public:
    MovingObject(ID id, Coord place, const Field &field, CoordinateView &view) : id(id),
                                                                                 place(place), field(field),
                                                                                 view(view) {}

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



