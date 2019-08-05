#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState
{
public:
    GameState() = default;

    GameState(const GameState& other) = delete;
    GameState& operator=(const GameState& other) = delete;

    GameState(const GameState&& other) = delete;
    GameState& operator=(const GameState&& other) = delete;

    virtual ~GameState() = default;

    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    virtual void updateImpl(sf::RenderWindow& window) = 0;
    virtual void drawImpl(sf::RenderWindow& window) = 0;
};

#endif
