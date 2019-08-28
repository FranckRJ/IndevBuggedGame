#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <cstddef>

#include "gameState.hpp"
#include "widgetCursor.hpp"
#include "widgetText.hpp"

class MainMenuState : public GameState
{
public:
    MainMenuState();

private:
    void updateImpl(sf::RenderWindow& pWindow) override;
    void drawImpl(sf::RenderWindow& pWindow) const override;

    void changeSelectedId(int pRelativePosition);

    void launchNewSelectedState();

    void centerWidgetInList();

private:
    WidgetText mNameOfGameText;
    std::array<WidgetText, 4> mListOfButton;
    WidgetCursor mCursorText;
    bool mChoiceIsSelected = false;
    std::size_t mCurrentId = 0;
};

#endif
