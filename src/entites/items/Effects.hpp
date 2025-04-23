#ifndef EFFECTS
#define EFFECTS

#include <functional>
#include "entites/gameObjects/Player.hpp" 

class Effects {
public:
    // ��������� ������-����� ����� std::function
    std::function<void(Player*)> SetFunc;
    std::function<void(Player*)> DeleteFunc;
};

#endif // !EFFECTS