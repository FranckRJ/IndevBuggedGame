#include "messageState.hpp"
#include "global.hpp"

MessageState::MessageState(std::vector<RectForMessage>& newListOfRect, sf::Text newMessageToShow)
{
    listOfRect = newListOfRect;
    messageToShow = newMessageToShow;
    timeToLeave = false;
    showMessage = false;
    numberOfEndOfIncrease = 0;
    time.restart();
}

void MessageState::update(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                Global::activeGameStateStack->pop();
                return;
            }
            else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
            {
                if (!timeToLeave)
                {
                    if (!showMessage)
                    {
                        for (RectForMessage& rect : listOfRect)
                        {
                            rect.rect.setSize(sf::Vector2f(rect.trueSize.x, rect.trueSize.y));
                            rect.rect.setOrigin((rect.rect.getSize().x - 1) / 2, (rect.rect.getSize().y - 1) / 2);
                            rect.rect.setPosition(rect.origin.x, rect.origin.y);
                            rect.endOfIncrease = true;
                        }
                        showMessage = true;
                    }
                    else
                    {
                        timeToLeave = true;
                        showMessage = false;
                        time.restart();
                    }
                }
            }
        }
    }

    for (auto it = listOfRect.begin(); it != listOfRect.end();)
    {
        if (!timeToLeave)
        {
            if (!(it->endOfIncrease))
            {
                if (time.getElapsedTime().asSeconds() > it->timeUntilStart)
                {
                    if (changeSizeOfRect(*it, it->speedIncrease, it->trueSize))
                    {
                        it->endOfIncrease = true;
                        ++numberOfEndOfIncrease;

                        if (numberOfEndOfIncrease == listOfRect.size())
                        {
                            showMessage = true;
                        }
                    }
                }
            }
        }
        else
        {
            if (time.getElapsedTime().asSeconds() > it->timeUntilHide)
            {
                if (changeSizeOfRect(*it, sf::Vector2i(-it->speedIncrease.x, -it->speedIncrease.y), sf::Vector2i(1, 1),
                                     -1))
                {
                    it = listOfRect.erase(it);
                    continue;
                }
            }
        }

        ++it;
    }

    if (listOfRect.empty())
    {
        Global::activeGameStateStack->pop();
        return;
    }
}

void MessageState::draw(sf::RenderWindow& window)
{
    Global::activeGameStateStack->oldDraw(window);

    window.setView(window.getDefaultView());

    for (RectForMessage& rect : listOfRect)
    {
        window.draw(rect.rect);
    }

    if (showMessage)
    {
        window.draw(messageToShow);
    }
}

bool MessageState::changeSizeOfRect(RectForMessage& rect, sf::Vector2i speed, sf::Vector2i endSize, int factor)
{
    rect.rect.setSize(sf::Vector2f(rect.rect.getSize().x + speed.x, rect.rect.getSize().y + speed.y));

    if (rect.rect.getSize().x * factor > endSize.x * factor)
    {
        rect.rect.setSize(sf::Vector2f(endSize.x, rect.rect.getSize().y));
    }
    if (rect.rect.getSize().y * factor > endSize.y * factor)
    {
        rect.rect.setSize(sf::Vector2f(rect.rect.getSize().x, endSize.y));
    }

    rect.rect.setOrigin((rect.rect.getSize().x - 1) / 2, (rect.rect.getSize().y - 1) / 2);
    rect.rect.setPosition(rect.origin.x, rect.origin.y);

    if (rect.rect.getSize().x == endSize.x && rect.rect.getSize().y == endSize.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
