#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "widgetText.hpp"
#include "widgetCursor.hpp"

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
    int maxId;
};

#endif
