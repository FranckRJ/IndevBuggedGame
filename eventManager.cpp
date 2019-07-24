#include "eventManager.hpp"
#include "utilities.hpp"

eventClass* eventManagerClass::createEvent(std::string eventName, sf::FloatRect newSurface, std::string additionnalInfo)
{
    return (new eventClass(getEventInfoFor(eventName, additionnalInfo), newSurface));
}

eventInfo eventManagerClass::getEventInfoFor(std::string eventName, std::string additionnalInfo)
{
    eventInfo infoForEvent;

    if (eventName == "UPDATE_EVENT")
    {
        infoForEvent.isUpdateEvent = true;
        infoForEvent.newVersion = utilitiesClass::readFirstString(additionnalInfo);
        infoForEvent.messageToShow = utilitiesClass::addNewLine(additionnalInfo);

        if (!infoForEvent.messageToShow.empty())
        {
            infoForEvent.isShowMessageEvent = true;
        }
    }
    else if (eventName == "MESSAGE_EVENT")
    {
        infoForEvent.isShowMessageEvent = true;
        infoForEvent.messageToShow = utilitiesClass::addNewLine(additionnalInfo);
    }

    return infoForEvent;
}
