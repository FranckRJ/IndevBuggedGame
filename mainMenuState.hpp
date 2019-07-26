#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "gameState.hpp"
#include "widgetCursor.hpp"
#include "widgetText.hpp"

class mainMenuStateClass : public gameStateClass
{
public:
    mainMenuStateClass();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void centerWidgetInList();

private:
    widgetTextClass nameOfGameText;
    std::vector<widgetTextClass> listOfButton;
    widgetCursorClass cursorText;
    bool choiceIsSelected;
    int currentId;
};

#endif
