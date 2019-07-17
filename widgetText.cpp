#include "widgetText.hpp"
#include "global.hpp"

widgetTextClass::widgetTextClass()
{
    messageToShow.setFont(global::font);
    messageToShow.setOrigin(0, static_cast<int>(messageToShow.getLocalBounds().top));
    numberOfTimeBlinkNeeded = 0;
    textIsBugged = true;
    isInBug = false;
}

widgetTextClass::widgetTextClass(std::string newMessage, sf::Color newColor, int newSize, int newPosX, int newPosY) :
    widgetTextClass()
{
    setMessage(newMessage);
    setFillColor(newColor);
    setSize(newSize);
    setPosition(newPosX, newPosY);
}

void widgetTextClass::update()
{
    if(numberOfTimeBlinkNeeded > 0 && messageToShow.getFillColor().a == 255 && timerForBlink.getElapsedTime().asSeconds() > 0.1)
    {
        sf::Color tmpColor = messageToShow.getFillColor();
        tmpColor.a = 127;
        messageToShow.setFillColor(tmpColor);
        --numberOfTimeBlinkNeeded;
        timerForBlink.restart();
    }

    if(messageToShow.getFillColor().a == 127 && timerForBlink.getElapsedTime().asSeconds() > 0.1)
    {
        sf::Color tmpColor = messageToShow.getFillColor();
        tmpColor.a = 255;
        messageToShow.setFillColor(tmpColor);
        timerForBlink.restart();
    }

    if(textIsBugged)
    {
        if(!isInBug)
        {
            if(timerForBug.getElapsedTime().asSeconds() > 0.5)
            {
                if(rand() % 100 < 15)
                {
                    int indexOfLetter = (rand() % (originalMessage.size() - 1)) + 1;
                    char newLetter = (rand() % (126 - 33)) + 33;
                    std::string newMessage = originalMessage;

                    newMessage[indexOfLetter] = newLetter;
                    setMessage(newMessage, false);

                    isInBug = true;
                }
                timerForBug.restart();
            }
        }
        else if(timerForBug.getElapsedTime().asSeconds() > 0.1)
        {
            setMessage(originalMessage);
            isInBug = false;
            timerForBug.restart();
        }
    }
}

void widgetTextClass::draw(sf::RenderWindow& window)
{
    window.draw(messageToShow);
}

int widgetTextClass::getNumberOfBlinkNeeded()
{
    return numberOfTimeBlinkNeeded;
}

sf::FloatRect widgetTextClass::getHitbox()
{
    return messageToShow.getGlobalBounds();
}

sf::Vector2f widgetTextClass::getPosition()
{
    return messageToShow.getPosition();
}

int widgetTextClass::getCentralVerticalPos()
{
    return (messageToShow.getPosition().y + (messageToShow.getGlobalBounds().height / 2));
}

void widgetTextClass::setNumberOfBlinkNeeded(int newNumber)
{
    numberOfTimeBlinkNeeded = newNumber;
}

void widgetTextClass::setCentralVerticalPos(int newPosY)
{
    setPosition(messageToShow.getPosition().x, newPosY - (messageToShow.getGlobalBounds().height / 2));
}

void widgetTextClass::setMessage(std::string newMessage, bool isOriginalMessage)
{
    messageToShow.setString(newMessage);
    if(isOriginalMessage)
    {
        originalMessage = newMessage;
        messageToShow.setOrigin(0, static_cast<int>(messageToShow.getLocalBounds().top));
    }
}

void widgetTextClass::setFillColor(sf::Color newColor)
{
    messageToShow.setFillColor(newColor);
}

void widgetTextClass::setSize(int newSize)
{
    messageToShow.setCharacterSize(newSize);
}

void widgetTextClass::setPosition(int newPosX, int newPosY)
{
    messageToShow.setPosition(newPosX, newPosY);
}
