#include "Level.hpp"


void Save(const std::string& path) {
    std::fstream file;
    file.open(path, std::fstream::out);
    if (file.is_open())
    {
        file << "LevelCounter: " << map.lvlCounter << "\n";
        file << "EndPos: " << endLevelPos.x << " " << endLevelPos.y << "\n\n";

        file << "[Floor]" << "\n";
        for (const std::vector<int> i : map.floor) {
            for (int j : i) {
                file << j;
            }
            file << "\n";
        }
        file << "\n";

        file << "[Wall]" << "\n";
        for (const std::vector<int> i : map.wall) {
            for (int j : i) {
                file << j;
            }
            file << "\n";
        }
        file << "\n";

        file << "[Fiature]" << "\n";
        for (const std::vector<int> i : map.shader) {
            for (int j : i) {
                file << j;
            }
            file << "\n";
        }
    }
    file.close();
}

void Load(const std::string& path) {

    std::fstream file;
    std::string str, full, floor, wall, shader;
    full, floor, wall, fiature = "";
    file.open(path, std::fstream::in);
    if (file.is_open()) {
        while (std::getline(file, str)) {
            if (str == "[Floor]") {
                while (std::getline(file, str)) {
                    if (str == "") { break; }
                    floor += str + "\n";
                }
            }
            if (str == "[Wall]") {
                while (std::getline(file, str)) {
                    if (str == "") { break; }
                    wall += str + "\n";
                }
            }
            if (str == "[Fiature]") {
                while (std::getline(file, str)) {
                    if (str == "") { break; }
                    shader += str + "\n";
                }
            }
            else { full += str + "\n"; }
        }
    }
    file.close();

    map.lvlCounter = std::stoi(full.substr(full.find("LevelCounter") + 14, full.find("EndPos") - 1 - (full.find("LevelCounter") + 13)));
    endLevelPos.x = std::stoi(full.substr(full.find("EndPos") + 8, full.find(" ", full.find("EndPos") + 8) - (full.find("EndPos") + 8)));
    endLevelPos.y = std::stoi(full.substr(full.find(" ", full.find("EndPos") + 9), full.find("\n", full.find("EndPos"))));

    int X = size(floor.substr(0, floor.find("\n"))); //����� �� X �����
    int Y = (size(floor)) / (X + 1); //����� �� Y �����
    std::vector<int> s(X);

    int x = 0, y = 0;

    for (char i : floor) {
        if (x == 0) {
            map.floor.push_back(s);
        }
        if (i != '\n') {
            map.floor[y][x] = (int)i - 48;
            x++;
        }
        else { y++; x = 0; }
    }

    x = 0;
    y = 0;

    for (char i : wall) {
        if (x == 0) {
            map.wall.push_back(s);
        }
        if (i != '\n') {
            map.wall[y][x] = (int)i - 48;
            x++;
        }
        else { y++; x = 0; }
    }

    x = 0;
    y = 0;

    for (char i : shader) {
        if (x == 0) {
            map.shader.push_back(s);
        }
        if (i != '\n') {
            map.shader[y][x] = (int)i - 48;
            x++;
        }
        else { y++; x = 0; }
    }
}
