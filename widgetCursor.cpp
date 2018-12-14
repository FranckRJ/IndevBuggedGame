#include "widgetCursor.hpp"

widgetCursorClass::widgetCursorClass() : widgetTextClass()
{
    maxSpeed = 20;
    currentSpeed = 0;
    acceleration = 4;
    positionToReach = getCentralVerticalPos();
    textIsBugged = false;
}

widgetCursorClass::widgetCursorClass(std::string newMessage, sf::Color newColor, int newSize, int newPosX, int newPosY) :
    widgetTextClass(newMessage, newColor, newSize, newPosX, newPosY)
{

}

void widgetCursorClass::update()
{
    if(currentSpeed == 0)
    {
        if(getCentralVerticalPos() != positionToReach)
        {
            if(positionToReach > getCentralVerticalPos())
            {
                currentSpeed += acceleration;
            }
            else
            {
                currentSpeed -= acceleration;
            }
        }
    }

    setPosition(messageToShow.getPosition().x, messageToShow.getGlobalBounds().top + currentSpeed);

    if(currentSpeed > 0)
    {
        if(getCentralVerticalPos() >= positionToReach)
        {
            setCentralVerticalPos(positionToReach);
            currentSpeed = 0;
        }
        else
        {
            currentSpeed += acceleration;
            if(currentSpeed > maxSpeed)
            {
                currentSpeed = maxSpeed;
            }
        }
    }
    else if(currentSpeed < 0)
    {
        if(getCentralVerticalPos() <= positionToReach)
        {
            setCentralVerticalPos(positionToReach);
            currentSpeed = 0;
        }
        else
        {
            currentSpeed -= acceleration;
            if(currentSpeed < -maxSpeed)
            {
                currentSpeed = -maxSpeed;
            }
        }
    }
}

void widgetCursorClass::setCentralVerticalPos(int newPosY)
{
    widgetTextClass::setCentralVerticalPos(newPosY);

    if(currentSpeed == 0)
    {
        positionToReach = getCentralVerticalPos();
    }
}

void widgetCursorClass::setPosition(int newPosX, int newPosY)
{
    widgetTextClass::setPosition(newPosX, newPosY);

    if(currentSpeed == 0)
    {
        positionToReach = getCentralVerticalPos();
    }
}

void widgetCursorClass::setPositionToReach(int newPosY)
{
    positionToReach = newPosY;
}
