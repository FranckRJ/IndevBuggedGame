#include <utility>

#include "gameStateStack.hpp"
#include "utls.hpp"

void GameStateStack::set(std::unique_ptr<GameState> pState)
{
    mListOfStates.clear();
    add(std::move(pState));
}

void GameStateStack::add(std::unique_ptr<GameState> pState)
{
    mStackHasChanged = true;
    mListOfStates.emplace_back(std::move(pState));
}

void GameStateStack::addBeforeLast(std::unique_ptr<GameState> pState)
{
    if (mListOfStates.size() > 0)
    {
        auto lastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 1));
        mStackHasChanged = true;
        mListOfStates.emplace(lastIte, std::move(pState));
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

void GameStateStack::update(sf::RenderWindow& pWindow)
{
    if (!mListOfStates.empty())
    {
        mListOfStates.back()->update(pWindow);
    }
}

void GameStateStack::updateBeforeLast(sf::RenderWindow& pWindow)
{
    if (mListOfStates.size() > 1)
    {
        auto beforeLastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 2));
        (*beforeLastIte)->update(pWindow);
    }
}

void GameStateStack::draw(sf::RenderWindow& pWindow) const
{
    if (!mListOfStates.empty())
    {
        mListOfStates.back()->draw(pWindow);
    }
}

void GameStateStack::drawBeforeLast(sf::RenderWindow& pWindow) const
{
    if (mListOfStates.size() >= 2)
    {
        auto beforeLastIte = std::next(mListOfStates.begin(), utls::asSigned(mListOfStates.size() - 2));
        (*beforeLastIte)->draw(pWindow);
    }
}

bool GameStateStack::stackHasChanged() const
{
    return mStackHasChanged;
}

void GameStateStack::resetStackHasChanged()
{
    mStackHasChanged = false;
}
