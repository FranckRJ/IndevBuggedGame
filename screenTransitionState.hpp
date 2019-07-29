#ifndef SCREENTRANSITION_HPP
#define SCREENTRANSITION_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "gameState.hpp"

class ScreenTransitionState : public GameState
{
public:
    ScreenTransitionState(std::unique_ptr<GameState>&& newState, sf::Color color, int newSpeed);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<GameState> stateToSet;
    sf::RectangleShape fadeEffect;
    int speedOfFade;
};

#endif
