#include "screenTransitionState.hpp"
#include "global.hpp"

screenTransitionStateClass::screenTransitionStateClass(std::unique_ptr<gameStateClass>&& newState, sf::Color color, int newSpeed) : stateToSet(std::move(newState))
{
    sf::Color colorOfFadeEffect = color;
    speedOfFade = newSpeed;

    colorOfFadeEffect.a = 0;
    fadeEffect.setFillColor(colorOfFadeEffect);
    fadeEffect.setSize(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN));
}

void screenTransitionStateClass::update(sf::RenderWindow& window)
{
    sf::Event event;
    sf::Color newColor = fadeEffect.getFillColor();

    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if(speedOfFade > 0)
    {
        if(newColor.a + speedOfFade >= 255)
        {
            newColor.a = 255;
            speedOfFade = -speedOfFade;
            global::activeGameStateStack->popBefore();
            global::activeGameStateStack->addBefore(std::move(stateToSet));
            stateToSet.release(); //normalement pas utile mais on sait jamais.
        }
        else
        {
            newColor.a += speedOfFade;
        }
    }
    else
    {
        if(newColor.a + speedOfFade <= 0)
        {
            global::activeGameStateStack->pop();
            return;
        }
        else
        {
            newColor.a += speedOfFade;
        }
    }

    fadeEffect.setFillColor(newColor);
}

void screenTransitionStateClass::draw(sf::RenderWindow& window)
{
    global::activeGameStateStack->oldDraw(window);

    window.setView(window.getDefaultView());

    window.draw(fadeEffect);
}
