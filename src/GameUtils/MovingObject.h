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

    bool up() {
        return moveIfPossible({place.x, place.y - 1});
    }

    bool down() {
        return moveIfPossible({place.x, place.y + 1});
    }

    bool left() {
        return moveIfPossible({place.x - 1, place.y});
    }

    bool right() {
        return moveIfPossible({place.x + 1, place.y});
    }

    void goTowards(const Coord& to_pos) {

        Coord betweenVec = to_pos - place;

        // этот ужас конечно же надо почистить, но пока чтош
        // this crazy mess of cource needs some clean up, but for now oh well...
        if (abs(betweenVec.x) > abs(betweenVec.y)) {
            if (betweenVec.x > 0) {

                if (!right()) {

                    if (betweenVec.y > 0) {
                        down();
                    }
                    else {
                        up();
                    }
                }
            }
            else {
                if (!left()) {

                    if (betweenVec.y > 0) {
                        down();
                    }
                    else {
                        up();
                    }
                }
            }
        }
        else {
            if (betweenVec.y > 0) {
                if (!down()) {

                    if (betweenVec.x > 0) {

                        right();
                    }
                    else {

                        left();
                    }
                }
            }
            else {
                if (!up()) {

                    if (betweenVec.x > 0) {

                        right();
                    }
                    else {

                        left();
                    }

                }
            }
        }
    }
};



