#include <utility>

#include "gameStateStack.hpp"
#include "utls.hpp"

void GameStateStack::set(std::unique_ptr<GameState> state)
{
    mListOfStates.clear();
    add(std::move(state));
}

void GameStateStack::add(std::unique_ptr<GameState> state)
{
    mStackHasChanged = true;
    mListOfStates.emplace_back(std::move(state));
}

void GameStateStack::addBeforeLast(std::unique_ptr<GameState> state)
{
    if (mListOfStates.size() > 0)
    {
        auto lastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 1));
        mStackHasChanged = true;
        mListOfStates.emplace(lastIte, std::move(state));
    }
}

void GameStateStack::pop()
{
    mStackHasChanged = true;
    mListOfStates.pop_back();
}

void GameStateStack::popBeforeLast()
{
    if (mListOfStates.size() > 1)
    {
        auto beforeLastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 2));
        mStackHasChanged = true;
        mListOfStates.erase(beforeLastIte);
    }
}

void GameStateStack::update(sf::RenderWindow& window)
{
    if (!mListOfStates.empty())
    {
        mListOfStates.back()->update(window);
    }
}

void GameStateStack::updateBeforeLast(sf::RenderWindow& window)
{
    if (mListOfStates.size() > 1)
    {
        auto beforeLastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 2));
        (*beforeLastIte)->update(window);
    }
}

void GameStateStack::draw(sf::RenderWindow& window)
{
    if (!mListOfStates.empty())
    {
        mListOfStates.back()->draw(window);
    }
}

void GameStateStack::drawBeforeLast(sf::RenderWindow& window)
{
    if (mListOfStates.size() >= 2)
    {
        auto beforeLastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 2));
        (*beforeLastIte)->draw(window);
    }
}

bool GameStateStack::stackHasChanged()
{
    return mStackHasChanged;
}

void GameStateStack::resetStackHasChanged()
{
    mStackHasChanged = false;
}
