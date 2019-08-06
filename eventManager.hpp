#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "event.hpp"

class EventManager
{
public:
    static std::unique_ptr<EventClass> createEvent(std::string eventName, sf::IntRect newSurface,
                                                   std::string additionnalInfo);
    static EventInfo getEventInfoFor(std::string eventName, std::string additionnalInfo);
};

#endif
