#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <SFML/Graphics.hpp>

#include "event.hpp"

class eventManagerClass
{
public:
    static eventClass* createEvent(std::string eventName, sf::FloatRect newSurface, std::string additionnalInfo);
    static eventInfo getEventInfoFor(std::string eventName, std::string additionnalInfo);
};

#endif
