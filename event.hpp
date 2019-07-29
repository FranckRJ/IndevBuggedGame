#ifndef EVENT_HPP
#define EVENT_HPP

#include <SFML/Graphics.hpp>

#include "versionNumber.hpp"

struct EventInfo
{
    bool isUpdateEvent = false;
    bool isShowMessageEvent = false;
    std::string messageToShow;
    VersionNumber newVersion;
};

class EventClass
{
public:
    EventClass(EventInfo newInfoForEvent, sf::IntRect newSurfaceOfEvent);
    bool isCollideWith(sf::IntRect collideBox);
    const EventInfo getEventInfo();

private:
    sf::IntRect surfaceOfEvent;
    EventInfo infoForEvent;
};

#endif
