#include "screenTransitionState.hpp"
#include "global.hpp"

ScreenTransitionState::ScreenTransitionState(std::unique_ptr<GameState> pState, sf::Color pColor, int pSpeed)
    : mStateToSet{std::move(pState)}, mSpeedOfFade{pSpeed}
{
    pColor.a = 0;
    mFadeEffect.setFillColor(pColor);
    mFadeEffect.setSize(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN));
}

void ScreenTransitionState::updateImpl(sf::RenderWindow& pWindow)
{
    auto event = sf::Event{};
    auto newColor = mFadeEffect.getFillColor();

    while (pWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            pWindow.close();
        }
    }

    if (mSpeedOfFade > 0)
    {
        if (newColor.a + mSpeedOfFade >= 255)
        {
            newColor.a = 255;
            mSpeedOfFade = -mSpeedOfFade;
            Global::activeGameStateStack->popBeforeLast();
            Global::activeGameStateStack->addBeforeLast(std::move(mStateToSet));
        }
        else
        {
            newColor.a += mSpeedOfFade;
        }
    }
    else
    {
        if (newColor.a + mSpeedOfFade <= 0)
        {
            Global::activeGameStateStack->pop();
            return;
        }
        else
        {
            newColor.a += mSpeedOfFade;
        }
    }

    mFadeEffect.setFillColor(newColor);
}

void ScreenTransitionState::drawImpl(sf::RenderWindow& pWindow) const
{
    Global::activeGameStateStack->drawBeforeLast(pWindow);

    pWindow.setView(pWindow.getDefaultView());

    pWindow.draw(mFadeEffect);
}
