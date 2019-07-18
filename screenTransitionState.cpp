#include "screenTransitionState.hpp"
#include "global.hpp"

screenTransitionStateClass::screenTransitionStateClass(gameStateClass* newState, sf::Color color, int newSpeed)
{
    sf::Color colorOfSprite = color;
    speed = newSpeed;

    colorOfSprite.a = 0;
    stateToAdd.reset(newState);
    sprite.setFillColor(colorOfSprite);
    sprite.setSize(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN));
}

void screenTransitionStateClass::update(sf::RenderWindow& window)
{
    sf::Event event;
    sf::Color newColor = sprite.getFillColor();

    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if(speed > 0)
    {
        if(newColor.a + speed >= 255)
        {
            newColor.a = 255;
            speed = -speed;
            global::activeGameStateStack->popBefore();
            global::activeGameStateStack->addBefore(std::unique_ptr<gameStateClass>(stateToAdd.release()));
        }
        else
        {
            newColor.a += speed;
        }
    }
    else
    {
        if(newColor.a + speed <= 0)
        {
            global::activeGameStateStack->pop();
            return;
        }
        else
        {
            newColor.a += speed;
        }
    }

    sprite.setFillColor(newColor);
}

void screenTransitionStateClass::draw(sf::RenderWindow& window)
{
    global::activeGameStateStack->oldDraw(window);

    window.setView(window.getDefaultView());

    window.draw(sprite);
}
