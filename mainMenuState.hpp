#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "gameState.hpp"
#include "widgetCursor.hpp"
#include "widgetText.hpp"

class MainMenuState : public GameState
{
public:
    MainMenuState();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void centerWidgetInList();

private:
    WidgetText nameOfGameText;
    std::vector<WidgetText> listOfButton;
    WidgetCursor cursorText;
    bool choiceIsSelected;
    int currentId;
};

#endif
