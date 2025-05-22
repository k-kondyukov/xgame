// !MAP
// author: ya_ntar
// basic map generation ticket
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "MapGenerator.h"

using IDType = int;
struct CellID {
    IDType wall;
    IDType floor;
    IDType shader;
};

/*class ItemIdField { //toDo: Подвязать ID, соответствующие этим объектам.
private:
    const size_t width, length;
    std::vector<std::vector<CellID>> id;


    int getWallID(const Wall &wall) {
        return 0;
    }

    int getFloorID(const Floor &floor) {
        return 0;
    }

    int getShaderID(const Shader &shader) {
        return 0;
    }

public:
    std::vector<CellID>& operator [](size_t i) {
        return id[i];
    };

    ItemIdField(const Field &field) :
            width(field.width), length(field.length),
            id(length, std::vector<CellID>(width)){

        for (int i = 0; i < field.val.size(); i++) {
            for (int j = 0; j < field.val[i].size(); ++j) {
                const Cell &currCell(field.val[i][j]);
                id[i][j].wall = getWallID(currCell.wall);
                id[i][j].floor = getFloorID(currCell.floor);
                id[i][j].shader = getShaderID(currCell.shader);
            }
        }

    }
};*/

class Map {
private:
    std::vector<Room> rooms;
    Field field;
/*    ItemIdField idField;*/

    int lvlCounter = 0;

public:

    Map(size_t width, size_t length, int numRooms = 5, size_t minRoomSize = 4, size_t maxRoomSize = 10):
    field{MapGenerator::getDungeon(width, length, numRooms, minRoomSize, maxRoomSize,WallType::Stone,rooms)}{
    }

    std::pair<Room, Room> findFurthestRooms(){
        return MapGenerator::findFurthestRooms(rooms);
    }
    void show() { // You can create map and call this method to look at the result
        for (int i = 0; i < field.height; ++i) {
            for (int j = 0; j < field.width; ++j) {
                if(field[i][j].wall.type == WallType::Nothing) {
                    std::cout << ' ';
                } else if (field[i][j].wall.orientation == WallOrientation::Front){
                    std::cout << '*';
                } else {
                    std::cout << '.';
                }
            }
            std::cout << '\n';
        }
    }

    const Field& getField(){
        return field;
    }




};
