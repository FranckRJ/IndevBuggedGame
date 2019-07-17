#ifndef SCREENTRANSITION_HPP
#define SCREENTRANSITION_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class screenTransitionStateClass : public gameStateClass
{
public:
    screenTransitionStateClass(gameStateClass* newState, sf::Color color, int newSpeed);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
private:
    std::unique_ptr<gameStateClass> stateToAdd;
    sf::RectangleShape sprite;
    int speed;
};

#endif
