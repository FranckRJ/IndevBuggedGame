#include "playState.hpp"

PlayState::PlayState(std::string nameOfLevel) : gameEngine(nameOfLevel)
{
}

void PlayState::updateImpl(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        gameEngine.jumpPlayer(spaceWasPressedLastFrame);
        spaceWasPressedLastFrame = true;
    }
    else
    {
        spaceWasPressedLastFrame = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        gameEngine.setPlayerDirection(Direction::LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        gameEngine.setPlayerDirection(Direction::RIGHT);
    }

    gameEngine.update();
}

void PlayState::drawImpl(sf::RenderWindow& window)
{
    window.clear(sf::Color(200, 200, 200));
    gameEngine.draw(window);
}
