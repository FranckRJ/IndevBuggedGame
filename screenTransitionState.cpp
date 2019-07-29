#include "screenTransitionState.hpp"
#include "global.hpp"

ScreenTransitionState::ScreenTransitionState(std::unique_ptr<GameState>&& newState, sf::Color color, int newSpeed)
    : stateToSet(std::move(newState))
{
    sf::Color colorOfFadeEffect = color;
    speedOfFade = newSpeed;

    colorOfFadeEffect.a = 0;
    fadeEffect.setFillColor(colorOfFadeEffect);
    fadeEffect.setSize(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN));
}

void ScreenTransitionState::update(sf::RenderWindow& window)
{
    sf::Event event;
    sf::Color newColor = fadeEffect.getFillColor();

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if (speedOfFade > 0)
    {
        if (newColor.a + speedOfFade >= 255)
        {
            newColor.a = 255;
            speedOfFade = -speedOfFade;
            Global::activeGameStateStack->popBefore();
            Global::activeGameStateStack->addBefore(std::move(stateToSet));
            stateToSet.release(); // normalement pas utile mais on sait jamais.
        }
        else
        {
            newColor.a += speedOfFade;
        }
    }
    else
    {
        if (newColor.a + speedOfFade <= 0)
        {
            Global::activeGameStateStack->pop();
            return;
        }
        else
        {
            newColor.a += speedOfFade;
        }
    }

    fadeEffect.setFillColor(newColor);
}

void ScreenTransitionState::draw(sf::RenderWindow& window)
{
    Global::activeGameStateStack->oldDraw(window);

    window.setView(window.getDefaultView());

    window.draw(fadeEffect);
}
