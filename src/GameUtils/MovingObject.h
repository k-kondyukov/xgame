#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "TextureManager.h"
#include "CoordinateView.h"
#include "../level/MapGenerator.h"

class MovingObject {
    ID id;
    Coord place;
    const Field &field;
    CoordinateView &view;

    void deleteView() { view.deleteImage(place, id); }

    void addView() { view.addImage(place, id); }

    void updatePov() {
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



