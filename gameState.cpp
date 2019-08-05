#include "gameState.hpp"

void GameState::update(sf::RenderWindow& window)
{
    updateImpl(window);
}

void GameState::draw(sf::RenderWindow& window)
{
    drawImpl(window);
}
