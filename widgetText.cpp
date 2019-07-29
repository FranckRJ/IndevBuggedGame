#include "widgetText.hpp"
#include "global.hpp"

WidgetText::WidgetText()
{
    messageToShow.setFont(Global::font);
    messageToShow.setOrigin(0, static_cast<int>(messageToShow.getLocalBounds().top));
    numberOfTimeBlinkNeeded = 0;
    textIsBugged = true;
    isInBug = false;
}

WidgetText::WidgetText(std::string newMessage, sf::Color newColor, int newSize, int newPosX, int newPosY) : WidgetText()
{
    setMessage(newMessage);
    setFillColor(newColor);
    setSize(newSize);
    setPosition(newPosX, newPosY);
}

void WidgetText::update()
{
    if (numberOfTimeBlinkNeeded > 0 && messageToShow.getFillColor().a == 255 &&
        timerForBlink.getElapsedTime().asSeconds() > 0.1)
    {
        sf::Color tmpColor = messageToShow.getFillColor();
        tmpColor.a = 127;
        messageToShow.setFillColor(tmpColor);
        --numberOfTimeBlinkNeeded;
        timerForBlink.restart();
    }

    if (messageToShow.getFillColor().a == 127 && timerForBlink.getElapsedTime().asSeconds() > 0.1)
    {
        sf::Color tmpColor = messageToShow.getFillColor();
        tmpColor.a = 255;
        messageToShow.setFillColor(tmpColor);
        timerForBlink.restart();
    }

    if (textIsBugged)
    {
        if (!isInBug)
        {
            if (timerForBug.getElapsedTime().asSeconds() > 0.5)
            {
                if (rand() % 100 < 15)
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
        else if (timerForBug.getElapsedTime().asSeconds() > 0.1)
        {
            setMessage(originalMessage);
            isInBug = false;
            timerForBug.restart();
        }
    }
}

void WidgetText::draw(sf::RenderWindow& window)
{
    window.draw(messageToShow);
}

int WidgetText::getNumberOfBlinkNeeded()
{
    return numberOfTimeBlinkNeeded;
}

sf::FloatRect WidgetText::getHitbox()
{
    return messageToShow.getGlobalBounds();
}

sf::Vector2f WidgetText::getPosition()
{
    return messageToShow.getPosition();
}

int WidgetText::getCentralVerticalPos()
{
    return (messageToShow.getPosition().y + (messageToShow.getGlobalBounds().height / 2));
}

void WidgetText::setNumberOfBlinkNeeded(int newNumber)
{
    numberOfTimeBlinkNeeded = newNumber;
}

void WidgetText::setCentralVerticalPos(int newPosY)
{
    setPosition(messageToShow.getPosition().x, newPosY - (messageToShow.getGlobalBounds().height / 2));
}

void WidgetText::setMessage(std::string newMessage, bool isOriginalMessage)
{
    messageToShow.setString(newMessage);
    if (isOriginalMessage)
    {
        originalMessage = newMessage;
        messageToShow.setOrigin(0, static_cast<int>(messageToShow.getLocalBounds().top));
    }
}

void WidgetText::setFillColor(sf::Color newColor)
{
    messageToShow.setFillColor(newColor);
}

void WidgetText::setSize(int newSize)
{
    messageToShow.setCharacterSize(newSize);
}

void WidgetText::setPosition(int newPosX, int newPosY)
{
    messageToShow.setPosition(newPosX, newPosY);
}
