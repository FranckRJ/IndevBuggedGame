#ifndef WIDGETTEXT_HPP
#define WIDGETTEXT_HPP

#include <SFML/Graphics.hpp>
#include <random>

class WidgetText
{
public:
    WidgetText();
    WidgetText(std::string newMessage, sf::Color newColor, int newSize, int newPosX = 0, int newPosY = 0);
    void update();
    void draw(sf::RenderWindow& window);
    int getNumberOfBlinkNeeded();
    sf::FloatRect getHitbox();
    sf::Vector2f getPosition();
    int getCentralVerticalPos();
    void setNumberOfBlinkNeeded(int newNumber);
    void setCentralVerticalPos(int newPosY);
    void setMessage(std::string newMessage, bool isOriginalMessage = true);
    void setFillColor(sf::Color newColor);
    void setSize(int newSize);
    void setPosition(int newPosX, int newPosY);

protected:
    std::uniform_int_distribution<char> randomChar{33, 126}; // '!' et '~'
    std::uniform_int_distribution<std::size_t> randomOriginalMessagePos;
    sf::Text messageToShow;
    std::string originalMessage;
    sf::Clock timerForBlink;
    sf::Clock timerForBug;
    int numberOfTimeBlinkNeeded;
    bool textIsBugged;
    bool isInBug;
};

#endif
