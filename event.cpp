#include "event.hpp"

EventClass::EventClass(EventInfo newInfoForEvent, sf::IntRect newSurfaceOfEvent)
{
    infoForEvent = newInfoForEvent;
    surfaceOfEvent = newSurfaceOfEvent;
}

bool EventClass::isCollideWith(sf::IntRect collideBox)
{
    return surfaceOfEvent.intersects(collideBox);
}

const EventInfo EventClass::getEventInfo()
{
    return infoForEvent;
}
