#include "mainMenuState.hpp"
#include "editLevelState.hpp"
#include "global.hpp"
#include "playState.hpp"
#include "screenTransitionState.hpp"

mainMenuStateClass::mainMenuStateClass()
{
    widgetTextClass playText;
    widgetTextClass editorText;
    widgetTextClass nothingText;
    widgetTextClass leaveText;

    currentId = 0;
    choiceIsSelected = false;

    nameOfGameText.setSize(60);
    nameOfGameText.setMessage("Indev Bugged Game");
    nameOfGameText.setFillColor(sf::Color::Green);
    nameOfGameText.setPosition(25, 25);

    playText.setSize(40);
    playText.setMessage("Jouer");
    playText.setFillColor(sf::Color::Green);

    editorText.setSize(40);
    editorText.setMessage("Editer");
    editorText.setFillColor(sf::Color::Green);

    nothingText.setSize(40);
    nothingText.setMessage("Rien");
    nothingText.setFillColor(sf::Color::Green);

    leaveText.setSize(40);
    leaveText.setMessage("Quitter");
    leaveText.setFillColor(sf::Color::Green);

    listOfButton.emplace_back(std::move(playText));
    listOfButton.emplace_back(std::move(editorText));
    listOfButton.emplace_back(std::move(nothingText));
    listOfButton.emplace_back(std::move(leaveText));

    centerWidgetInList();

    cursorText.setSize(50);
    cursorText.setMessage(">");
    cursorText.setFillColor(sf::Color::Green);
    cursorText.setPosition(listOfButton[currentId].getPosition().x - cursorText.getHitbox().width - 20, 0);

    cursorText.setCentralVerticalPos(listOfButton[currentId].getCentralVerticalPos());
    cursorText.setPositionToReach(listOfButton[currentId].getCentralVerticalPos());
}

void mainMenuStateClass::update(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed && !choiceIsSelected)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                --currentId;
                if (currentId < 0)
                {
                    currentId = listOfButton.size();
                }
                cursorText.setPositionToReach(listOfButton[currentId].getCentralVerticalPos());
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                ++currentId;
                if (currentId > listOfButton.size())
                {
                    currentId = 0;
                }
                cursorText.setPositionToReach(listOfButton[currentId].getCentralVerticalPos());
            }
            else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
            {
                if (currentId == 3)
                {
                    window.close();
                }
                else
                {
                    listOfButton[currentId].setNumberOfBlinkNeeded(3);
                    choiceIsSelected = true;
                }
            }
        }
    }

    if (choiceIsSelected && listOfButton[currentId].getNumberOfBlinkNeeded() == 0)
    {
        if (currentId == 0)
        {
            global::activeGameStateStack->add(std::make_unique<screenTransitionStateClass>(
                std::make_unique<playStateClass>("level1.txt"), sf::Color::Black, 25));
        }
        else if (currentId == 1)
        {
            global::activeGameStateStack->add(std::make_unique<screenTransitionStateClass>(
                std::make_unique<editLevelStateClass>("level6.txt"), sf::Color::Black, 25));
        }
        else if (currentId == 2)
        {
            global::activeGameStateStack->add(std::make_unique<screenTransitionStateClass>(
                std::make_unique<playStateClass>("level6.txt"), sf::Color::Black, 25));
        }

        choiceIsSelected = false;
    }

    for (widgetTextClass& thisWidget : listOfButton)
    {
        thisWidget.update();
    }
    nameOfGameText.update();
    cursorText.update();
}

void mainMenuStateClass::draw(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black);
    nameOfGameText.draw(window);
    cursorText.draw(window);

    for (widgetTextClass& thisWidget : listOfButton)
    {
        thisWidget.draw(window);
    }
}

void mainMenuStateClass::centerWidgetInList()
{
    int sizeOfAllWidgets = 0;
    int currentPositionForWidget = 0;
    int widthestWidgetSize = 0;

    for (widgetTextClass& thisWidget : listOfButton)
    {
        sizeOfAllWidgets += thisWidget.getHitbox().height + 20;

        if (thisWidget.getHitbox().width > widthestWidgetSize)
        {
            widthestWidgetSize = thisWidget.getHitbox().width;
        }
    }
    sizeOfAllWidgets -= 20;

    currentPositionForWidget = (HEIGHT_SCREEN / 2) - (sizeOfAllWidgets / 2) + 50;

    for (widgetTextClass& thisWidget : listOfButton)
    {
        thisWidget.setPosition((WIDTH_SCREEN / 2) - (widthestWidgetSize / 2), currentPositionForWidget);
        currentPositionForWidget += thisWidget.getHitbox().height + 20;
    }
}
