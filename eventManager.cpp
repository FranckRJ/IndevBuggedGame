#include "eventManager.hpp"
#include "utilities.hpp"

std::unique_ptr<Event> EventManager::createEvent(std::string pEventName, sf::IntRect pSurface,
                                                 std::string pAdditionnalInfo)
{
    return std::make_unique<Event>(eventInfoFor(pEventName, pAdditionnalInfo), pSurface);
}

EventInfo EventManager::eventInfoFor(std::string pEventName, std::string pAdditionnalInfo)
{
    auto infoForEvent = EventInfo{};

    if (pEventName == "UPDATE_EVENT")
    {
        infoForEvent.isUpdateEvent = true;
        infoForEvent.newVersion = Utilities::readFirstString(pAdditionnalInfo);
        infoForEvent.messageToShow = Utilities::addNewLine(pAdditionnalInfo);

        if (!infoForEvent.messageToShow.empty())
        {
            infoForEvent.isShowMessageEvent = true;
        }
    }
    else if (pEventName == "MESSAGE_EVENT")
    {
        infoForEvent.isShowMessageEvent = true;
        infoForEvent.messageToShow = Utilities::addNewLine(pAdditionnalInfo);
    }

    return infoForEvent;
}
