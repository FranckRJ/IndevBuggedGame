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
    EventClass(EventInfo newInfoForEvent, sf::FloatRect newSurfaceOfEvent);
    bool isCollideWith(sf::FloatRect collideBox);
    const EventInfo getEventInfo();

private:
    sf::FloatRect surfaceOfEvent;
    EventInfo infoForEvent;
};

#endif
