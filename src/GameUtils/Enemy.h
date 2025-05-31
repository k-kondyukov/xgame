#pragma once

#include "MovingObject.h"

class Enemy : public MovingObject {

    enum class EnemyState {
        wondering_around,
        chasing_player
    };

    EnemyState state = EnemyState::wondering_around;

    std::optional<MovingObject>* playerPtr;

public:
    Enemy(ID id, Coord place, const Field& field, CoordinateView& view, std::optional<MovingObject>* player) :
        MovingObject(id, place, field, view),
        playerPtr(player) {
    }

    void Action() {

        if (playerPtr) {

            if (field.isObjectVisible(place, playerPtr->value().getPlace())) {
                state = EnemyState::chasing_player;
            }
            else {
                state = EnemyState::wondering_around;
            }

            switch (state) {

            case EnemyState::wondering_around:

                moveRundomIfPossible();
                break;

            case EnemyState::chasing_player:

                Coord betweenVec = playerPtr->value().getPlace() - place;

                if (abs(betweenVec.x) > abs(betweenVec.y)) {
                    if (betweenVec.x > 0) {
                        right();
                    }
                    else {
                        left();
                    }
                }
                else {
                    if (betweenVec.y > 0) {
                        down();
                    }
                    else {
                        up();
                    }
                }

                break;
            }
        }

    }
};