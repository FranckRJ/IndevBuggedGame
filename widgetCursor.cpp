#include "widgetCursor.hpp"

WidgetCursor::WidgetCursor() : WidgetText()
{
    maxSpeed = 20;
    currentSpeed = 0;
    acceleration = 4;
    positionToReach = getCentralVerticalPos();
    textIsBugged = false;
}

WidgetCursor::WidgetCursor(std::string newMessage, sf::Color newColor, int newSize, int newPosX, int newPosY)
    : WidgetText(newMessage, newColor, newSize, newPosX, newPosY)
{
}

void WidgetCursor::update()
{
    if (currentSpeed == 0)
    {
        if (getCentralVerticalPos() != positionToReach)
        {
            if (positionToReach > getCentralVerticalPos())
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

    if (currentSpeed > 0)
    {
        if (getCentralVerticalPos() >= positionToReach)
        {
            setCentralVerticalPos(positionToReach);
            currentSpeed = 0;
        }
        else
        {
            currentSpeed += acceleration;
            if (currentSpeed > maxSpeed)
            {
                currentSpeed = maxSpeed;
            }
        }
    }
    else if (currentSpeed < 0)
    {
        if (getCentralVerticalPos() <= positionToReach)
        {
            setCentralVerticalPos(positionToReach);
            currentSpeed = 0;
        }
        else
        {
            currentSpeed -= acceleration;
            if (currentSpeed < -maxSpeed)
            {
                currentSpeed = -maxSpeed;
            }
        }
    }
}

void WidgetCursor::setCentralVerticalPos(int newPosY)
{
    WidgetText::setCentralVerticalPos(newPosY);

    if (currentSpeed == 0)
    {
        positionToReach = getCentralVerticalPos();
    }
}

void WidgetCursor::setPosition(int newPosX, int newPosY)
{
    WidgetText::setPosition(newPosX, newPosY);

    if (currentSpeed == 0)
    {
        positionToReach = getCentralVerticalPos();
    }
}

void WidgetCursor::setPositionToReach(int newPosY)
{
    positionToReach = newPosY;
}
