#include "gameStateStack.hpp"

gameStateStackClass::gameStateStackClass()
{
    change = false;
}

void gameStateStackClass::set(gameStateClass* state)
{
    listOfState.clear();
    add(state);
}

void gameStateStackClass::add(gameStateClass* state)
{
    change = true;
    listOfState.push_back(std::unique_ptr<gameStateClass>(state));
}

void gameStateStackClass::addBefore(gameStateClass* state)
{
    if(listOfState.size() > 0)
    {
        auto it = listOfState.end();
        change = true;
        --it;
        listOfState.insert(it, std::unique_ptr<gameStateClass>(state));
    }
}

void gameStateStackClass::pop()
{
    change = true;
    listOfState.pop_back();
}

void gameStateStackClass::popBefore()
{
    if(listOfState.size() >= 2)
    {
        auto it = listOfState.end();
        change = true;
        ----it;
        listOfState.erase(it);
    }
}

void gameStateStackClass::update(sf::RenderWindow& window)
{
    if(!listOfState.empty())
    {
        listOfState.back()->update(window);
    }
}

void gameStateStackClass::oldUpdate(sf::RenderWindow& window)
{
    if(listOfState.size() >= 2)
    {
        auto it = listOfState.rbegin();
        ++it;
        (*it)->update(window);
    }
}

void gameStateStackClass::draw(sf::RenderWindow& window)
{
    if(!listOfState.empty())
    {
        listOfState.back()->draw(window);
    }
}

void gameStateStackClass::oldDraw(sf::RenderWindow& window)
{
    if(listOfState.size() >= 2)
    {
        auto it = listOfState.rbegin();
        ++it;
        (*it)->draw(window);
    }
}

bool gameStateStackClass::getChange()
{
    return change;
}

void gameStateStackClass::setChange(bool newChange)
{
    change = newChange;
}
