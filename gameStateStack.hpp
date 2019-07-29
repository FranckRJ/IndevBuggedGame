#ifndef GAMESTATESTACK_HPP
#define GAMESTATESTACK_HPP

#include <list>
#include <memory>

#include "gameState.hpp"

class GameStateStack
{
public:
    void set(std::unique_ptr<GameState>&& state);
    void add(std::unique_ptr<GameState>&& state);
    void addBefore(std::unique_ptr<GameState>&& state);
    void pop();
    void popBefore();
    void update(sf::RenderWindow& window);
    void oldUpdate(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void oldDraw(sf::RenderWindow& window);
    bool getStackHasChanged();
    void resetStackHasChanged();

private:
    std::list<std::unique_ptr<GameState>> listOfStates;
    bool stackHasChanged = false;
};

#endif
