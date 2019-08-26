#include "gameState.hpp"

void GameState::update(sf::RenderWindow& pWindow)
{
    updateImpl(pWindow);
}

void GameState::draw(sf::RenderWindow& pWindow) const
{
    drawImpl(pWindow);
}
