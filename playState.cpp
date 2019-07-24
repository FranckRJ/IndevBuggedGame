#include "playState.hpp"

playStateClass::playStateClass(std::string nameOfLevel) : gamePlayed(nameOfLevel)
{
}

void playStateClass::update(sf::RenderWindow& window)
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
        gamePlayed.jumpPlayer();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        gamePlayed.movePlayerTo(direction::LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        gamePlayed.movePlayerTo(direction::RIGHT);
    }

    gamePlayed.update();
}

void playStateClass::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(200, 200, 200));
    gamePlayed.draw(window);
}
