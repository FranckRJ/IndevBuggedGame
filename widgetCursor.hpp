#ifndef WIDGETCURSOR_HPP
#define WIDGETCURSOR_HPP

#include <SFML/Graphics.hpp>

#include "widgetText.hpp"

class WidgetCursor : public WidgetText
{
public:
    WidgetCursor();
    WidgetCursor(std::string pMessage, sf::Color pColor, int pSize, sf::Vector2i pPos = {0, 0});

    void initialize();

    void updateImpl() override;

    void positionHasChanged() override;

    void setPositionToReach(int pPosY);

private:
    int mMaxSpeed = 20;
    int mCurrentSpeed = 0;
    int mAcceleration = 4;
    int mPositionToReach = 0;
};

#endif
