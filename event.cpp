#include "event.hpp"

EventClass::EventClass(EventInfo newInfoForEvent, sf::FloatRect newSurfaceOfEvent)
{
    infoForEvent = newInfoForEvent;
    surfaceOfEvent = newSurfaceOfEvent;
}

bool EventClass::isCollideWith(sf::FloatRect collideBox)
{
    return surfaceOfEvent.intersects(collideBox);
}

const EventInfo EventClass::getEventInfo()
{
    return infoForEvent;
}
