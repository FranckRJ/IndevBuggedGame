#include "event.hpp"

eventClass::eventClass(eventInfo newInfoForEvent, sf::FloatRect newSurfaceOfEvent)
{
    infoForEvent = newInfoForEvent;
    surfaceOfEvent = newSurfaceOfEvent;
}

bool eventClass::isCollideWith(sf::FloatRect collideBox)
{
    return surfaceOfEvent.intersects(collideBox);
}

const eventInfo eventClass::getEventInfo()
{
    return infoForEvent;
}
