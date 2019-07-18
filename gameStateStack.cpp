#include <utility>

#include "gameStateStack.hpp"

void gameStateStackClass::set(std::unique_ptr<gameStateClass>&& state)
{
    listOfStates.clear();
    add(std::move(state));
}

void gameStateStackClass::add(std::unique_ptr<gameStateClass>&& state)
{
    stackHasChanged = true;
    listOfStates.emplace_back(std::move(state));
}

void gameStateStackClass::addBefore(std::unique_ptr<gameStateClass>&& state)
{
    if(listOfStates.size() > 0)
    {
        auto it = listOfStates.end();
        stackHasChanged = true;
        --it;
        listOfStates.emplace(it, std::move(state));
    }
}

void gameStateStackClass::pop()
{
    stackHasChanged = true;
    listOfStates.pop_back();
}

void gameStateStackClass::popBefore()
{
    if(listOfStates.size() >= 2)
    {
        auto it = listOfStates.end();
        stackHasChanged = true;
        ----it;
        listOfStates.erase(it);
    }
}

void gameStateStackClass::update(sf::RenderWindow& window)
{
    if(!listOfStates.empty())
    {
        listOfStates.back()->update(window);
    }
}

void gameStateStackClass::oldUpdate(sf::RenderWindow& window)
{
    if(listOfStates.size() >= 2)
    {
        auto it = listOfStates.rbegin();
        ++it;
        (*it)->update(window);
    }
}

void gameStateStackClass::draw(sf::RenderWindow& window)
{
    if(!listOfStates.empty())
    {
        listOfStates.back()->draw(window);
    }
}

void gameStateStackClass::oldDraw(sf::RenderWindow& window)
{
    if(listOfStates.size() >= 2)
    {
        auto it = listOfStates.rbegin();
        ++it;
        (*it)->draw(window);
    }
}

bool gameStateStackClass::getStackHasChanged()
{
    return stackHasChanged;
}

void gameStateStackClass::resetStackHasChanged()
{
    stackHasChanged = false;
}
