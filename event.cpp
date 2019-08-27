#include "event.hpp"

Event::Event(EventInfo pInfoForEvent, sf::IntRect pSurfaceOfEvent)
    : mEventInfo{pInfoForEvent}, mSurfaceOfEvent{pSurfaceOfEvent}
{
}

bool Event::isCollideWith(sf::IntRect pCollideBox)
{
    return mSurfaceOfEvent.intersects(pCollideBox);
}

const EventInfo Event::eventInfo()
{
    return mEventInfo;
}
