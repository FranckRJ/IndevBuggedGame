#ifndef GAME_HPP
#define GAME_HPP

#include "gameStateStack.hpp"

class Game
{
public:
    Game();
    void run();

private:
    GameStateStack gameStateStack;
    sf::RenderWindow window;
};

#endif
