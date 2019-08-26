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

class Event
{
public:
    Event(EventInfo pInfoForEvent, sf::IntRect pSurfaceOfEvent);

    bool isCollideWith(sf::IntRect pCollideBox);
    const EventInfo eventInfo();

private:
    const EventInfo mEventInfo;
    const sf::IntRect mSurfaceOfEvent;
};

#endif
