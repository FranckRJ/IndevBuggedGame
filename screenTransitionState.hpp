#ifndef SCREENTRANSITION_HPP
#define SCREENTRANSITION_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "gameState.hpp"

class ScreenTransitionState : public GameState
{
public:
    ScreenTransitionState(std::unique_ptr<GameState> pState, sf::Color pColor, int pSpeed);

private:
    void updateImpl(sf::RenderWindow& pWindow) override;
    void drawImpl(sf::RenderWindow& pWindow) const override;

private:
    std::unique_ptr<GameState> mStateToSet;
    sf::RectangleShape mFadeEffect;
    int mSpeedOfFade;
};

#endif
