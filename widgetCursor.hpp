#ifndef WIDGETCURSOR_HPP
#define WIDGETCURSOR_HPP

#include <SFML/Graphics.hpp>

#include "widgetText.hpp"

class widgetCursorClass : public widgetTextClass
{
public:
    widgetCursorClass();
    widgetCursorClass(std::string newMessage, sf::Color newColor, int newSize, int newPosX = 0, int newPosY = 0);
    void update();
    void setCentralVerticalPos(int newPosY);
    void setPosition(int newPosX, int newPosY);
    void setPositionToReach(int newPosY);
private:
    int maxSpeed;
    int currentSpeed;
    int acceleration;
    int positionToReach;
};

#endif
