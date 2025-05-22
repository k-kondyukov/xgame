// !MAP
// author: ya_ntar
// basic map generation ticket
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "MapGenerator.h"


class Map {
private:
    size_t width;
    size_t length;
    int numRooms;
    size_t minRoomSize;
    size_t maxRoomSize;
    int lvlCounter = 0;
    std::vector<Room> rooms;
    Field field;

public:

    Map(size_t width, size_t length, int numRooms = 5, size_t minRoomSize = 4, size_t maxRoomSize = 10) :
            width(width),
            length(length),
            numRooms(numRooms),
            minRoomSize(minRoomSize),
            maxRoomSize(maxRoomSize),

            field{MapGenerator::getDungeon(width, length, numRooms, minRoomSize, maxRoomSize, WallType::Stone, rooms)} {
    }

    void regenerate() {
        field = Field(MapGenerator::getDungeon(width, length, numRooms, minRoomSize, maxRoomSize, WallType::Stone, rooms));
    }

    std::pair<Room, Room> findFurthestRooms() {
        return MapGenerator::findFurthestRooms(rooms);
    }

    void show() { // You can create map and call this method to look at the result
        for (int i = 0; i < field.getHeight(); ++i) {
            for (int j = 0; j < field.getWidth(); ++j) {
                if (field[i][j].wall.type == WallType::Nothing) {
                    std::cout << ' ';
                } else if (field[i][j].wall.orientation == WallOrientation::Front) {
                    std::cout << '*';
                } else {
                    std::cout << '.';
                }
            }
            std::cout << '\n';
        }
    }

    const Field &getField() {
        return field;
    }


};
