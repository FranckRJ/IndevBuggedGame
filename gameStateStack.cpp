#include <utility>

#include "gameStateStack.hpp"

void GameStateStack::set(std::unique_ptr<GameState>&& state)
{
    listOfStates.clear();
    add(std::move(state));
}

void GameStateStack::add(std::unique_ptr<GameState>&& state)
{
    stackHasChanged = true;
    listOfStates.emplace_back(std::move(state));
}

void GameStateStack::addBefore(std::unique_ptr<GameState>&& state)
{
    if (listOfStates.size() > 0)
    {
        auto it = listOfStates.end();
        stackHasChanged = true;
        --it;
        listOfStates.emplace(it, std::move(state));
    }
}

void GameStateStack::pop()
{
    stackHasChanged = true;
    listOfStates.pop_back();
}

void GameStateStack::popBefore()
{
    if (listOfStates.size() >= 2)
    {
        auto it = listOfStates.end();
        stackHasChanged = true;
        ----it;
        listOfStates.erase(it);
    }
}

void GameStateStack::update(sf::RenderWindow& window)
{
    if (!listOfStates.empty())
    {
        listOfStates.back()->update(window);
    }
}

void GameStateStack::oldUpdate(sf::RenderWindow& window)
{
    if (listOfStates.size() >= 2)
    {
        auto it = listOfStates.rbegin();
        ++it;
        (*it)->update(window);
    }
}

void GameStateStack::draw(sf::RenderWindow& window)
{
    if (!listOfStates.empty())
    {
        listOfStates.back()->draw(window);
    }
}

void GameStateStack::oldDraw(sf::RenderWindow& window)
{
    if (listOfStates.size() >= 2)
    {
        auto it = listOfStates.rbegin();
        ++it;
        (*it)->draw(window);
    }
}

bool GameStateStack::getStackHasChanged()
{
    return stackHasChanged;
}

void GameStateStack::resetStackHasChanged()
{
    stackHasChanged = false;
}
