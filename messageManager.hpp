#ifndef MESSAGEMANAGER_HPP
#define MESSAGEMANAGER_HPP

#include <unordered_map>

#include "messageState.hpp"

class messageManagerClass
{
public:
    static void initialize();
    static std::pair<std::vector<rectForMessage>, sf::Text> getInfoForMessage(std::string nameOfMessage);
    static void addMessageStateToStack(std::string nameOfMessage, std::string messageToShow);

private:
    static inline std::unordered_map<std::string, std::pair<std::vector<rectForMessage>, sf::Text>> listOfMessage;
};

#endif
