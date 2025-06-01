#pragma once

#include "MovingObject.h"

class Enemy : public MovingObject {

    enum class EnemyState {
        wondering_around,
        going_to_last_seen_player_pos,
        chasing_player
    };

    EnemyState state = EnemyState::wondering_around;

    std::optional<MovingObject>* playerPtr;

    Coord last_seen_player_pos;

public:
    Enemy(ID id, Coord place, const Field& field, CoordinateView& view, std::optional<MovingObject>* player) :
        MovingObject(id, place, field, view),
        playerPtr(player) {
    }

    void Action() {

        if (playerPtr) {

            if (field.isObjectVisible(place, playerPtr->value().getPlace())) {
                state = EnemyState::chasing_player;
                last_seen_player_pos = playerPtr->value().getPlace();
            }
            else {
                if (state == EnemyState::chasing_player) {
                    state = EnemyState::going_to_last_seen_player_pos;
                }
                if (state == EnemyState::going_to_last_seen_player_pos && place == last_seen_player_pos) {
                    state = EnemyState::wondering_around;
                }
            }

            switch (state) {

            case EnemyState::wondering_around:

                moveRundomIfPossible();
                break;

            case EnemyState::going_to_last_seen_player_pos:

                goTowards(last_seen_player_pos);
                break;

            case EnemyState::chasing_player:

                goTowards(playerPtr->value().getPlace());
                break;
            }
        }

    }
};