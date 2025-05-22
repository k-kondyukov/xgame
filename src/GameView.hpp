#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>
#include "level/Level.hpp"
#include "Observer.hpp"
#include "Resources/Resources.hpp"

class GameView : public Observer {
private:
    sf::RenderWindow& window;
    Level& level;
    sf::RenderTexture levelTexture;

    void rebuildLevelTexture();

    void drawMap();
public:
    GameView(sf::RenderWindow& win, Level& lvl);
    ~GameView() override = default;

    void update() override;
    void draw();
};

#endif // GAMEVIEW_HPP