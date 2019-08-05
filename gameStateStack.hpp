#ifndef GAMESTATESTACK_HPP
#define GAMESTATESTACK_HPP

#include <memory>
#include <vector>

#include "gameState.hpp"

class GameStateStack
{
public:
    void set(std::unique_ptr<GameState> pState);
    void add(std::unique_ptr<GameState> pState);
    void addBeforeLast(std::unique_ptr<GameState> pState);
    void pop();
    void popBeforeLast();
    void update(sf::RenderWindow& pWindow);
    void updateBeforeLast(sf::RenderWindow& pWindow);
    void draw(sf::RenderWindow& pWindow);
    void drawBeforeLast(sf::RenderWindow& pWindow);
    bool stackHasChanged();
    void resetStackHasChanged();

private:
    std::vector<std::unique_ptr<GameState>> mListOfStates;
    bool mStackHasChanged = false;
};

#endif
