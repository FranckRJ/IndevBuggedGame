#include "messageManager.hpp"
#include "global.hpp"

void MessageManager::initialize()
{
    {
        std::vector<RectForMessage> listOfRect;
        sf::Text messageToShow;

        messageToShow.setFont(Global::font);
        messageToShow.setCharacterSize(20);
        messageToShow.setFillColor(sf::Color::Green);
        messageToShow.setPosition(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

        listOfRect.push_back(RectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(0, 0, 0, 128));
        listOfRect.back().speedIncrease = sf::Vector2i(30, 30);
        listOfRect.back().speedDecrease = sf::Vector2i(30, 30);
        listOfRect.back().trueSize.x = (WIDTH_SCREEN / 10) * 9;
        listOfRect.back().trueSize.y = (HEIGHT_SCREEN / 10) * 9;
        listOfRect.back().timeUntilHide = 0.1;

        listOfRect.push_back(RectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(0, 0, 0, 128));
        listOfRect.back().speedIncrease = sf::Vector2i(30, 30);
        listOfRect.back().speedDecrease = sf::Vector2i(30, 30);
        listOfRect.back().trueSize.x = (WIDTH_SCREEN / 10) * 8;
        listOfRect.back().trueSize.y = (HEIGHT_SCREEN / 10) * 8;
        listOfRect.back().timeUntilStart = 0.1;

        listOfMessage["NORMAL_MESSAGE"] = std::pair<std::vector<RectForMessage>, sf::Text>(listOfRect, messageToShow);
    }

    {
        std::vector<RectForMessage> listOfRect;
        sf::Text messageToShow;

        messageToShow.setFont(Global::font);
        messageToShow.setCharacterSize(20);
        messageToShow.setFillColor(sf::Color::Blue);
        messageToShow.setPosition(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

        listOfRect.push_back(RectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(255, 255, 255, 200));
        listOfRect.back().rect.setSize(sf::Vector2f(WIDTH_SCREEN, HEIGHT_SCREEN));
        listOfRect.back().speedIncrease = sf::Vector2i(1000, 1000);
        listOfRect.back().speedDecrease = sf::Vector2i(1000, 1000);
        listOfRect.back().trueSize.x = WIDTH_SCREEN;
        listOfRect.back().trueSize.y = HEIGHT_SCREEN;

        listOfRect.push_back(RectForMessage());
        listOfRect.back().origin = sf::Vector2i(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
        listOfRect.back().rect.setFillColor(sf::Color(0, 0, 0, 0));
        listOfRect.back().speedIncrease = sf::Vector2i(1000, 1000);
        listOfRect.back().speedDecrease = sf::Vector2i(1000, 1000);
        listOfRect.back().trueSize.x = WIDTH_SCREEN;
        listOfRect.back().trueSize.y = HEIGHT_SCREEN;
        listOfRect.back().timeUntilStart = 3;

        listOfMessage["CRASH_MESSAGE"] = std::pair<std::vector<RectForMessage>, sf::Text>(listOfRect, messageToShow);
    }
}

std::pair<std::vector<RectForMessage>, sf::Text> MessageManager::getInfoForMessage(std::string nameOfMessage)
{
    auto infos = listOfMessage.find(nameOfMessage);

    if (infos != listOfMessage.end())
    {
        return infos->second;
    }
    else
    {
        return std::pair<std::vector<RectForMessage>, sf::Text>(std::vector<RectForMessage>(), sf::Text());
    }
}

void MessageManager::addMessageStateToStack(std::string nameOfMessage, std::string messageToShow)
{
    std::pair<std::vector<RectForMessage>, sf::Text> infos = getInfoForMessage(nameOfMessage);

    infos.second.setString(messageToShow);
    infos.second.setOrigin(infos.second.getGlobalBounds().width / 2, infos.second.getGlobalBounds().height / 2);
    infos.second.setPosition(infos.second.getPosition());

    Global::activeGameStateStack->add(std::make_unique<MessageState>(infos.first, infos.second));
}
