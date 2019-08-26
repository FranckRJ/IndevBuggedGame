#ifndef WIDGETTEXT_HPP
#define WIDGETTEXT_HPP

#include <SFML/Graphics.hpp>
#include <random>

class WidgetText
{
public:
    WidgetText();
    WidgetText(std::string pMessage, sf::Color pColor, int pSize, sf::Vector2i pPos = {0, 0});

    WidgetText(const WidgetText& pOther) = delete;
    WidgetText& operator=(const WidgetText& pOther) = delete;

    WidgetText(const WidgetText&& pOther) = delete;
    WidgetText& operator=(const WidgetText&& pOther) = delete;

    virtual ~WidgetText() = default;

    void update();
    virtual void updateImpl();
    void draw(sf::RenderWindow& pWindow);

    int numberOfBlinkNeeded() const;
    void setNumberOfBlinkNeeded(int pNumber);

    sf::Vector2i position() const;
    void setPosition(sf::Vector2i pPos);

    int centralVerticalPos() const;
    void setCentralVerticalPos(int pPosY);

    virtual void positionHasChanged();

    void setSize(int pSize);

    sf::IntRect hitbox() const;

    void setFillColor(sf::Color pColor);

    void setMessage(std::string pMessage, bool pIsOriginalMessage = true);

protected:
    std::uniform_int_distribution<char> mRandomChar{33, 126}; // '!' et '~'
    std::uniform_int_distribution<std::size_t> mRandomOriginalMessagePos;
    sf::Text mMessageToShow;
    std::string mOriginalMessage;
    sf::Clock mTimerForBlink;
    sf::Clock mTimerForBug;
    int mNumberOfTimeBlinkNeeded = 0;
    bool mTextIsBugged = true;
    bool mIsInBug = false;
};

#endif
