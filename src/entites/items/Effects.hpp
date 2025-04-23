#ifndef EFFECTS
#define EFFECTS

#include <functional>
#include "entites/gameObjects/Player.hpp" 

class Effects {
public:
    // ־בתÿגכÿול כÿלבהא-קכוםû קונוח std::function
    std::function<void(Player*)> SetFunc;
    std::function<void(Player*)> DeleteFunc;
};

#endif // !EFFECTS