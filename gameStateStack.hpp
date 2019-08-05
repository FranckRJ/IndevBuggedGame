#ifndef GAMESTATESTACK_HPP
#define GAMESTATESTACK_HPP

#include <memory>
#include <vector>

#include "gameState.hpp"

class GameStateStack
{
public:
    void set(std::unique_ptr<GameState> state);
    void add(std::unique_ptr<GameState> state);
    void addBeforeLast(std::unique_ptr<GameState> state);
    void pop();
    void popBeforeLast();
    void update(sf::RenderWindow& window);
    void updateBeforeLast(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void drawBeforeLast(sf::RenderWindow& window);
    bool stackHasChanged();
    void resetStackHasChanged();

private:
    std::vector<std::unique_ptr<GameState>> mListOfStates;
    bool mStackHasChanged = false;
};

#endif
