// author: ya_ntar
// basic map generation ticket
#pragma once

#include <cstddef>
#include <vector>
#include <random>
#include <optional>
#include <set>
#include <queue>
#include <cmath>

struct Room {
    int x, y, w, h;
};
struct Dungeon {
    std::vector<std::vector<bool>> map;
    std::vector<Room> rooms;
};

class DungeonGenerator {


    static bool intersects(const Room &a, const Room &b) {
        return (a.x < b.x + b.w && a.x + a.w > b.x &&
                a.y < b.y + b.h && a.y + a.h > b.y);
    }

    static void digRoom(std::vector<std::vector<bool>> &map, const Room &room) {
        for (int y = room.y + 1; y < room.y + room.h - 1; ++y) {
            for (int x = room.x + 1; x < room.x + room.w - 1; ++x) {
                map[y][x] = true; // пол
            }
        }
    }

    static void digCorridor(std::vector<std::vector<bool>> &map, const Room &a, const Room &b) {
        int x1 = a.x + a.w / 2;
        int y1 = a.y + a.h / 2;
        int x2 = b.x + b.w / 2;
        int y2 = b.y + b.h / 2;

        if (rand() % 2) {
            for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
                map[y1][x] = true;
            for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
                map[y][x2] = true;
        } else {
            for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
                map[y][x1] = true;
            for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
                map[y2][x] = true;
        }
    }

public:

    static Dungeon generateDungeon(
            size_t width,
            size_t height,
            size_t numRooms,
            size_t minRoomSize,
            size_t maxRoomSize
    ) {
        srand(static_cast<unsigned>(time(0)));

        Dungeon dungeon;
        dungeon.map = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));

        for (int i = 0; i < numRooms; ++i) {
            Room room;
            room.w = minRoomSize + rand() % (maxRoomSize - minRoomSize + 1);
            room.h = minRoomSize + rand() % (maxRoomSize - minRoomSize + 1);
            room.x = rand() % (width - room.w - 1) + 1;
            room.y = rand() % (height - room.h - 1) + 1;

            bool overlaps = false;
            for (const auto &other: dungeon.rooms) {
                if (intersects(room, other)) {
                    overlaps = true;
                    break;
                }
            }

            if (!overlaps) {
                digRoom(dungeon.map, room);
                if (!dungeon.rooms.empty())
                    digCorridor(dungeon.map, dungeon.rooms.back(), room);
                dungeon.rooms.push_back(room);
            } else {
                --i;
            }
        }

        return dungeon;
    }

    static void printMap(const std::vector<std::vector<bool>> &map) { // for debug purposes
        for (const auto &row: map) {
            for (bool cell: row)
                std::cout << (cell ? '.' : ' ');
            std::cout << '\n';
        }
    }

};


enum class Floor {
    None,
    DefaultFloor
};

enum class Shader {
    Default
};

enum class WallType {
    Nothing,
    Stone,
    Wood
};

enum class WallOrientation {
    Front,
    Full,
    LDCorner,
    RDCorner,
    LUCorner,
    RUCorner
};

struct Wall {
    WallOrientation orientation;
    WallType type;

    Wall(WallOrientation orientation, WallType type)
            : orientation(orientation), type(type) {};
};

struct Cell {
    Shader shader = Shader::Default;
    Floor floor = Floor::DefaultFloor;
    Wall wall{WallOrientation::Front, WallType::Nothing};
    [[nodiscard]] bool passable() const{
        return wall.type == WallType::Nothing;
    }
};

class Field {
    size_t width, height;
    std::vector<std::vector<Cell>> val;

public:
    [[nodiscard]] size_t getWidth() const{
        return width;
    }
    [[nodiscard]] size_t getHeight() const{
        return height;
    }
    std::vector<Cell> &operator[](size_t i) {
        return val[i];
    };
    const std::vector<Cell> &operator[](size_t i) const {
        return val[i];
    };

    Field(size_t width, size_t length)
            : width(width), height(length), val(length, std::vector<Cell>(width)) {}
};


class MapGenerator {


public:


    static void changeToEmpty(Field &field) {
        SetAllCellFloorsTo(field, Floor::DefaultFloor);
        SetAllCellShadersTo(field, Shader::Default);
        SetAllCellWallsTo(field, {WallOrientation::Front, WallType::Stone});
    }

    static void SetAllCellWallsTo(Field &field, Wall wall) {
        for (size_t i = 0; i < field.getHeight(); ++i)
            for (size_t j = 0; j < field.getWidth(); ++j)
                field[i][j].wall = wall;
    }

    static void SetAllCellShadersTo(Field &field, Shader shader) {
        for (size_t i = 0; i < field.getHeight(); ++i)
            for (size_t j = 0; j < field.getWidth(); ++j)
                field[i][j].shader = shader;
    }

    static void SetAllCellFloorsTo(Field &field, Floor floor) {
        for (size_t i = 0; i < field.getHeight(); ++i)
            for (size_t j = 0; j < field.getWidth(); ++j)
                field[i][j].floor = floor;
    }

    static void buildRoomWalls(Field &field, WallType type = WallType::Stone) {
        for (size_t y = 1; y < field.getHeight() - 1; ++y) {
            for (size_t x = 1; x < field.getWidth() - 1; ++x) {
                if (field[y][x].wall.type == WallType::Nothing) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        for (int dx = -1; dx <= 1; ++dx) {
                            if (field[y + dy][x + dx].wall.type != WallType::Nothing)
                                field[y + dy][x + dx].wall.type = type;
                        }
                    }
                }
            }
        }
    }

    static void drawBorderWalls(Field &field, Dungeon &dungeon, size_t i, size_t j) {
        if (i > 0 && !dungeon.map[i - 1][j]) {
            field[i - 1][j].wall.orientation = WallOrientation::Front;
        }
        // Generation of other borders, style dependent

        /* if (j > 0 && !dungeon.map[i][j - 1]){
             field[i][j - 1].wall.orientation = WallOrientation::Front;
         }
         if (i < dungeon.map.size() - 1 && !dungeon.map[i + 1][j]){
             field[i + 1][j].wall.orientation = WallOrientation::Front;
         }
         if (j < dungeon.map[i].size() - 1 && !dungeon.map[i][j + 1]){
             field[i][j + 1].wall.orientation = WallOrientation::Front;
         }*/

    }


    static Field getRoom(size_t width, size_t length, WallType type = WallType::Stone) {
        Field field{width, length};
        buildRoomWalls(field, type);
        return field;
    }

    static Field getDungeon(size_t width, size_t length, size_t numRooms, size_t minRoomSize, size_t maxRoomSize,
                            WallType type, std::vector<Room> &rooms) {
        Field field{width, length};
        SetAllCellWallsTo(field, {WallOrientation::Full, WallType::Stone});
        auto dungeon = DungeonGenerator::generateDungeon(width, length, numRooms, minRoomSize, maxRoomSize);
        rooms = dungeon.rooms;
        //DungeonGenerator::printMap(dungeon.map); to check how it looks
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; ++j) {
                if (dungeon.map[i][j]) {
                    field[i][j].wall.type = WallType::Nothing;
                    field[i][j].floor = Floor::DefaultFloor;
                    drawBorderWalls(field, dungeon, i, j);
                }

            }
        }
        return field;
    }

    static float calculateDistance(const Room &a, const Room &b) {
        float centerAX = a.x + a.w / 2.0f;
        float centerAY = a.y + a.h / 2.0f;
        float centerBX = b.x + b.w / 2.0f;
        float centerBY = b.y + b.h / 2.0f;

        return std::sqrt(std::pow(centerBX - centerAX, 2) +
                         std::pow(centerBY - centerAY, 2));
    };

    static std::pair<Room, Room> findFurthestRooms(const std::vector<Room> &rooms) {
        if (rooms.size() < 2) {
            throw std::runtime_error("Need at least 2 rooms");
        }

        Room roomA = rooms[0];
        Room roomB = rooms[1];
        float maxDistance = 0.0f;


        for (size_t i = 0; i < rooms.size(); ++i) {
            for (size_t j = i + 1; j < rooms.size(); ++j) {
                float currentDistance = calculateDistance(rooms[i], rooms[j]);
                if (currentDistance > maxDistance) {
                    maxDistance = currentDistance;
                    roomA = rooms[i];
                    roomB = rooms[j];
                }
            }
        }

        return {roomA, roomB};
    }

};

