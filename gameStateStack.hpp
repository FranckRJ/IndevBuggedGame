#ifndef GAMESTATESTACK_HPP
#define GAMESTATESTACK_HPP

#include <list>
#include <memory>

#include "gameState.hpp"

class gameStateStackClass
{
public:
    void set(std::unique_ptr<gameStateClass>&& state);
    void add(std::unique_ptr<gameStateClass>&& state);
    void addBefore(std::unique_ptr<gameStateClass>&& state);
    void pop();
    void popBefore();
    void update(sf::RenderWindow& window);
    void oldUpdate(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void oldDraw(sf::RenderWindow& window);
    bool getStackHasChanged();
    void resetStackHasChanged();
private:
    std::list<std::unique_ptr<gameStateClass>> listOfStates;
    bool stackHasChanged = false;
};

#endif
