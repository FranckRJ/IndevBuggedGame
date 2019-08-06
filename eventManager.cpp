#include "eventManager.hpp"
#include "utilities.hpp"

std::unique_ptr<EventClass> EventManager::createEvent(std::string eventName, sf::IntRect newSurface,
                                                      std::string additionnalInfo)
{
    return std::make_unique<EventClass>(getEventInfoFor(eventName, additionnalInfo), newSurface);
}

EventInfo EventManager::getEventInfoFor(std::string eventName, std::string additionnalInfo)
{
    EventInfo infoForEvent;

    if (eventName == "UPDATE_EVENT")
    {
        infoForEvent.isUpdateEvent = true;
        infoForEvent.newVersion = Utilities::readFirstString(additionnalInfo);
        infoForEvent.messageToShow = Utilities::addNewLine(additionnalInfo);

        if (!infoForEvent.messageToShow.empty())
        {
            infoForEvent.isShowMessageEvent = true;
        }
    }
    else if (eventName == "MESSAGE_EVENT")
    {
        infoForEvent.isShowMessageEvent = true;
        infoForEvent.messageToShow = Utilities::addNewLine(additionnalInfo);
    }

    return infoForEvent;
}
