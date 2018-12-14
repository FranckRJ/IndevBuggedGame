#ifndef MESSAGESTATE_HPP
#define MESSAGESTATE_HPP

#include "gameState.hpp"

struct rectForMessage
{
    rectForMessage() : endOfIncrease(false), timeUntilStart(0), timeUntilHide(0) {}
    bool endOfIncrease;
    double timeUntilStart;
    double timeUntilHide;
    sf::Vector2i origin;
    sf::Vector2i trueSize;
    sf::Vector2i speedIncrease;
    sf::Vector2i speedDecrease;
    sf::RectangleShape rect;
};

class messageStateClass : public gameStateClass
{
public:
    messageStateClass(std::vector<rectForMessage>& newListOfRect, sf::Text newMessageToShow);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool changeSizeOfRect(rectForMessage& rect, sf::Vector2i speed, sf::Vector2i endSize, int factor = 1);
private:
    sf::Clock time;
    bool timeToLeave;
    bool showMessage;
    unsigned int numberOfEndOfIncrease;
    std::vector<rectForMessage> listOfRect;
    sf::Text messageToShow;
};

#endif
