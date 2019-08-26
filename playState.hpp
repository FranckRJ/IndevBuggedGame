#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameEngine.hpp"
#include "gameState.hpp"

class PlayState : public GameState
{
public:
    PlayState(std::string nameOfLevel);

private:
    void updateImpl(sf::RenderWindow& window) override;
    void drawImpl(sf::RenderWindow& window) const override;

private:
    GameEngine gameEngine;
    bool spaceWasPressedLastFrame = false;
};

#endif
