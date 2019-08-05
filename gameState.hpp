#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState
{
public:
    GameState() = default;

    GameState(const GameState& pOther) = delete;
    GameState& operator=(const GameState& pOther) = delete;

    GameState(const GameState&& pOther) = delete;
    GameState& operator=(const GameState&& pOther) = delete;

    virtual ~GameState() = default;

    void update(sf::RenderWindow& pWindow);
    void draw(sf::RenderWindow& pWindow);

private:
    virtual void updateImpl(sf::RenderWindow& pWindow) = 0;
    virtual void drawImpl(sf::RenderWindow& pWindow) = 0;
};

#endif
