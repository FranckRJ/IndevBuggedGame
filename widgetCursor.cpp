#include "widgetCursor.hpp"
#include "utls.hpp"

WidgetCursor::WidgetCursor() : WidgetText()
{
    initialize();
}

WidgetCursor::WidgetCursor(std::string pMessage, sf::Color pColor, int pSize, sf::Vector2i pPos)
    : WidgetText(pMessage, pColor, pSize, pPos)
{
    initialize();
}

void WidgetCursor::initialize()
{
    mPositionToReach = centralVerticalPos();
    setTextIsBugged(false);
}

void WidgetCursor::updateImpl()
{
    if (mCurrentSpeed == 0)
    {
        if (centralVerticalPos() != mPositionToReach)
        {
            if (mPositionToReach > centralVerticalPos())
            {
                mCurrentSpeed += mAcceleration;
            }
            else
            {
                mCurrentSpeed -= mAcceleration;
            }
        }
    }

    setPosition({position().x, hitbox().top + mCurrentSpeed});

    if (mCurrentSpeed > 0)
    {
        if (centralVerticalPos() >= mPositionToReach)
        {
            setCentralVerticalPos(mPositionToReach);
            mCurrentSpeed = 0;
        }
        else
        {
            mCurrentSpeed += mAcceleration;
            if (mCurrentSpeed > mMaxSpeed)
            {
                mCurrentSpeed = mMaxSpeed;
            }
        }
    }
    else if (mCurrentSpeed < 0)
    {
        if (centralVerticalPos() <= mPositionToReach)
        {
            setCentralVerticalPos(mPositionToReach);
            mCurrentSpeed = 0;
        }
        else
        {
            mCurrentSpeed -= mAcceleration;
            if (mCurrentSpeed < -mMaxSpeed)
            {
                mCurrentSpeed = -mMaxSpeed;
            }
        }
    }
}

void WidgetCursor::positionHasChanged()
{
    if (mCurrentSpeed == 0)
    {
        mPositionToReach = centralVerticalPos();
    }
}

void WidgetCursor::setPositionToReach(int pPosY)
{
    mPositionToReach = pPosY;
}
