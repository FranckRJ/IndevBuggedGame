#ifndef SCREENTRANSITION_HPP
#define SCREENTRANSITION_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class screenTransitionStateClass : public gameStateClass
{
public:
    screenTransitionStateClass(std::unique_ptr<gameStateClass>&& newState, sf::Color color, int newSpeed);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
private:
    std::unique_ptr<gameStateClass> stateToSet;
    sf::RectangleShape fadeEffect;
    int speedOfFade;
};

#endif
