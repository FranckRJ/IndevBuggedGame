#ifndef EVENT_HPP
#define EVENT_HPP

#include <SFML/Graphics.hpp>

struct eventInfo
{
    bool isUpdateEvent = false;
    bool isShowMessageEvent = false;
    std::string messageToShow;
    double newVersion;
};

class eventClass
{
public:
    eventClass(eventInfo newInfoForEvent, sf::FloatRect newSurfaceOfEvent);
    bool isCollideWith(sf::FloatRect collideBox);
    const eventInfo getEventInfo();
private:
    sf::FloatRect surfaceOfEvent;
    eventInfo infoForEvent;
};

#endif
