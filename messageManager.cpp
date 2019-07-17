#include "messageManager.hpp"
#include "global.hpp"

std::unordered_map<std::string, std::pair<std::vector<rectForMessage>, sf::Text>> messageManagerClass::listOfMessage;

void messageManagerClass::initialize()
{
    {
        std::vector<rectForMessage> listOfRect;
        sf::Text messageToShow;

        messageToShow.setFont(global::font);
        messageToShow.setCharacterSize(20);
        messageToShow.setFillColor(sf::Color::Green);
        messageToShow.setPosition(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

        listOfRect.push_back(rectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(0, 0, 0, 128));
        listOfRect.back().speedIncrease = sf::Vector2i(30, 30);
        listOfRect.back().speedDecrease = sf::Vector2i(30, 30);
        listOfRect.back().trueSize.x = (WIDTH_SCREEN / 10) * 9;
        listOfRect.back().trueSize.y = (HEIGHT_SCREEN / 10) * 9;
        listOfRect.back().timeUntilHide = 0.25;

        listOfRect.push_back(rectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(0, 0, 0, 128));
        listOfRect.back().speedIncrease = sf::Vector2i(30, 30);
        listOfRect.back().speedDecrease = sf::Vector2i(30, 30);
        listOfRect.back().trueSize.x = (WIDTH_SCREEN / 10) * 8;
        listOfRect.back().trueSize.y = (HEIGHT_SCREEN / 10) * 8;
        listOfRect.back().timeUntilStart = 0.25;

        listOfMessage["NORMAL_MESSAGE"] = std::pair<std::vector<rectForMessage>, sf::Text>(listOfRect, messageToShow);
    }

    {
        std::vector<rectForMessage> listOfRect;
        sf::Text messageToShow;

        messageToShow.setFont(global::font);
        messageToShow.setCharacterSize(20);
        messageToShow.setFillColor(sf::Color::Blue);
        messageToShow.setPosition(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

        listOfRect.push_back(rectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(255, 255, 255, 200));
        listOfRect.back().rect.setSize(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN));
        listOfRect.back().speedIncrease = sf::Vector2i(1000, 1000);
        listOfRect.back().speedDecrease = sf::Vector2i(1000, 1000);
        listOfRect.back().trueSize.x = WIDTH_SCREEN;
        listOfRect.back().trueSize.y = HEIGHT_SCREEN;

        listOfRect.push_back(rectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(0, 0, 0, 0));
        listOfRect.back().speedIncrease = sf::Vector2i(1000, 1000);
        listOfRect.back().speedDecrease = sf::Vector2i(1000, 1000);
        listOfRect.back().trueSize.x = WIDTH_SCREEN;
        listOfRect.back().trueSize.y = HEIGHT_SCREEN;
        listOfRect.back().timeUntilStart = 5;

        listOfMessage["CRASH_MESSAGE"] = std::pair<std::vector<rectForMessage>, sf::Text>(listOfRect, messageToShow);
    }
}

std::pair<std::vector<rectForMessage>, sf::Text> messageManagerClass::getInfoForMessage(std::string nameOfMessage)
{
    auto infos = listOfMessage.find(nameOfMessage);

    if(infos != listOfMessage.end())
    {
        return infos->second;
    }
    else
    {
        return std::pair<std::vector<rectForMessage>, sf::Text>(std::vector<rectForMessage>(), sf::Text());
    }
}

void messageManagerClass::addMessageStateToStack(std::string nameOfMessage, std::string messageToShow)
{
    std::pair<std::vector<rectForMessage>, sf::Text> infos = getInfoForMessage(nameOfMessage);

    infos.second.setString(messageToShow);
    infos.second.setOrigin(infos.second.getGlobalBounds().width / 2, infos.second.getGlobalBounds().height / 2);
    infos.second.setPosition(infos.second.getPosition());

    global::activeGameStateStack->add(new messageStateClass(infos.first, infos.second));
}
