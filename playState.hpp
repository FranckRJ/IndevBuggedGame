#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameEngine.hpp"
#include "gameState.hpp"

class PlayState : public GameState
{
public:
    PlayState(std::string nameOfLevel);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    GameEngine gameEngine;
    bool spaceWasPressedLastFrame = false;
};

#endif
