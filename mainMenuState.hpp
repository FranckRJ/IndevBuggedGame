#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <array>

#include "gameState.hpp"
#include "widgetCursor.hpp"
#include "widgetText.hpp"

class MainMenuState : public GameState
{
public:
    MainMenuState();

private:
    void updateImpl(sf::RenderWindow& window) override;
    void drawImpl(sf::RenderWindow& window) override;
    void centerWidgetInList();

private:
    WidgetText nameOfGameText;
    std::array<WidgetText, 4> listOfButton;
    WidgetCursor cursorText;
    bool choiceIsSelected;
    int currentId;
};

#endif
