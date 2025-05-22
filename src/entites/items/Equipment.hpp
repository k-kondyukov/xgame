#ifndef EQUIPMENT
#define EQUIPMENT

#include <functional>
#include "entites/gameObjects/Player.hpp" 

class Equipment {
public:
    // ��������� ������-����� ����� std::function
    std::function<void(Player*)> Equip;
    std::function<void(Player*)> TakeOff;
};

#endif // !EQUIPMENT