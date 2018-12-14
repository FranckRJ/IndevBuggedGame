#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameState.hpp"
#include "gamePlayed.hpp"

class playStateClass : public gameStateClass
{
public:
    playStateClass(std::string nameOfLevel);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
private:
    gamePlayedClass gamePlayed;
};

#endif
