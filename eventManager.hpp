#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "event.hpp"

class EventManager
{
public:
    static std::unique_ptr<Event> createEvent(std::string pEventName, sf::IntRect pSurface,
                                              std::string pAdditionnalInfo);
    static EventInfo eventInfoFor(std::string pEventName, std::string pAdditionnalInfo);
};

#endif
