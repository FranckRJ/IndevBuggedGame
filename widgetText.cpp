#include "widgetText.hpp"
#include "global.hpp"
#include "utls.hpp"

WidgetText::WidgetText()
{
    mMessageToShow.setFont(Global::font);
    mMessageToShow.setOrigin(0, utls::intFloor(mMessageToShow.getLocalBounds().top));
}

WidgetText::WidgetText(std::string pMessage, sf::Color pColor, int pSize, sf::Vector2i pPos) : WidgetText()
{
    setMessage(pMessage);
    setFillColor(pColor);
    setSize(pSize);
    setPosition(pPos);
}

void WidgetText::update()
{
    updateImpl();
}

void WidgetText::updateImpl()
{
    if (mNumberOfTimeBlinkNeeded > 0 && mMessageToShow.getFillColor().a == 255 &&
        mTimerForBlink.getElapsedTime().asSeconds() > 0.1f)
    {
        auto tmpColor = mMessageToShow.getFillColor();
        tmpColor.a = 127;
        mMessageToShow.setFillColor(tmpColor);
        --mNumberOfTimeBlinkNeeded;
        mTimerForBlink.restart();
    }

    if (mMessageToShow.getFillColor().a == 127 && mTimerForBlink.getElapsedTime().asSeconds() > 0.1f)
    {
        auto tmpColor = mMessageToShow.getFillColor();
        tmpColor.a = 255;
        mMessageToShow.setFillColor(tmpColor);
        mTimerForBlink.restart();
    }

    if (mTextIsBugged)
    {
        if (!mIsInBug)
        {
            if (mTimerForBug.getElapsedTime().asSeconds() > 0.5f)
            {
                if (Global::randomPercentage(Global::fast_random) < 15)
                {
                    std::size_t indexOfLetter = mRandomOriginalMessagePos(Global::fast_random);
                    char newLetter = mRandomChar(Global::fast_random);
                    std::string newMessage = mOriginalMessage;

                    newMessage[indexOfLetter] = newLetter;
                    setMessage(newMessage, false);

                    mIsInBug = true;
                }
                mTimerForBug.restart();
            }
        }
        else if (mTimerForBug.getElapsedTime().asSeconds() > 0.1f)
        {
            setMessage(mOriginalMessage);
            mIsInBug = false;
            mTimerForBug.restart();
        }
    }
}

void WidgetText::draw(sf::RenderWindow& pWindow)
{
    pWindow.draw(mMessageToShow);
}

int WidgetText::numberOfBlinkNeeded() const
{
    return mNumberOfTimeBlinkNeeded;
}

void WidgetText::setNumberOfBlinkNeeded(int pNumber)
{
    mNumberOfTimeBlinkNeeded = pNumber;
}

sf::Vector2i WidgetText::position() const
{
    const auto pos = mMessageToShow.getPosition();
    return sf::Vector2i(utls::intFloor(pos.x), utls::intFloor(pos.y));
}

void WidgetText::setPosition(sf::Vector2i pPos)
{
    mMessageToShow.setPosition(pPos.x, pPos.y);
    positionHasChanged();
}

int WidgetText::centralVerticalPos() const
{
    return utls::intFloor(mMessageToShow.getPosition().y + (mMessageToShow.getGlobalBounds().height / 2.f));
}

void WidgetText::setCentralVerticalPos(int pPosY)
{
    setPosition({utls::intFloor(mMessageToShow.getPosition().x),
                 pPosY - utls::intFloor(mMessageToShow.getGlobalBounds().height / 2.f)});
}

void WidgetText::positionHasChanged()
{
}

void WidgetText::setSize(int pSize)
{
    mMessageToShow.setCharacterSize(utls::asUnsigned(pSize));
}

sf::IntRect WidgetText::hitbox() const
{
    auto messageHitbox = mMessageToShow.getGlobalBounds();

    return sf::IntRect{utls::intFloor(messageHitbox.left), utls::intFloor(messageHitbox.top),
                       utls::intFloor(messageHitbox.width), utls::intFloor(messageHitbox.height)};
}

void WidgetText::setTextIsBugged(bool pTextIsBugged)
{
    mTextIsBugged = pTextIsBugged;
}

void WidgetText::setFillColor(sf::Color pColor)
{
    mMessageToShow.setFillColor(pColor);
}

void WidgetText::setMessage(std::string pMessage, bool pIsOriginalMessage)
{
    mMessageToShow.setString(pMessage);
    if (pIsOriginalMessage)
    {
        mOriginalMessage = pMessage;
        mRandomOriginalMessagePos = std::uniform_int_distribution<std::size_t>{0, mOriginalMessage.size() - 1};
        mMessageToShow.setOrigin(0, mMessageToShow.getLocalBounds().top);
    }
}
