#include "mainMenuState.hpp"
#include "editLevelState.hpp"
#include "global.hpp"
#include "playState.hpp"
#include "screenTransitionState.hpp"

MainMenuState::MainMenuState()
{
    currentId = 0;
    choiceIsSelected = false;

    nameOfGameText.setSize(60);
    nameOfGameText.setMessage("Indev Bugged Game");
    nameOfGameText.setFillColor(sf::Color::Green);
    nameOfGameText.setPosition({25, 25});

    listOfButton[0].setSize(40);
    listOfButton[0].setMessage("Jouer");
    listOfButton[0].setFillColor(sf::Color::Green);

    listOfButton[1].setSize(40);
    listOfButton[1].setMessage("Editer");
    listOfButton[1].setFillColor(sf::Color::Green);

    listOfButton[2].setSize(40);
    listOfButton[2].setMessage("Rien");
    listOfButton[2].setFillColor(sf::Color::Green);

    listOfButton[3].setSize(40);
    listOfButton[3].setMessage("Quitter");
    listOfButton[3].setFillColor(sf::Color::Green);

    centerWidgetInList();

    cursorText.setSize(50);
    cursorText.setMessage(">");
    cursorText.setFillColor(sf::Color::Green);
    cursorText.setPosition({listOfButton[currentId].position().x - cursorText.hitbox().width - 20, 0});

    cursorText.setCentralVerticalPos(listOfButton[currentId].centralVerticalPos());
    cursorText.setPositionToReach(listOfButton[currentId].centralVerticalPos());
}

void MainMenuState::updateImpl(sf::RenderWindow& window)
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
                    currentId = listOfButton.size() - 1;
                }
                cursorText.setPositionToReach(listOfButton[currentId].centralVerticalPos());
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                ++currentId;
                if (currentId >= listOfButton.size())
                {
                    currentId = 0;
                }
                cursorText.setPositionToReach(listOfButton[currentId].centralVerticalPos());
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

    if (choiceIsSelected && listOfButton[currentId].numberOfBlinkNeeded() == 0)
    {
        if (currentId == 0)
        {
            Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
                std::make_unique<PlayState>("level1.txt"), sf::Color::Black, 25));
        }
        else if (currentId == 1)
        {
            Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
                std::make_unique<EditLevelState>("level7.txt"), sf::Color::Black, 25));
        }
        else if (currentId == 2)
        {
            Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
                std::make_unique<PlayState>("level6.txt"), sf::Color::Black, 25));
        }

        choiceIsSelected = false;
    }

    for (WidgetText& thisWidget : listOfButton)
    {
        thisWidget.update();
    }
    nameOfGameText.update();
    cursorText.update();
}

void MainMenuState::drawImpl(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black);
    nameOfGameText.draw(window);
    cursorText.draw(window);

    for (WidgetText& thisWidget : listOfButton)
    {
        thisWidget.draw(window);
    }
}

void MainMenuState::centerWidgetInList()
{
    int sizeOfAllWidgets = 0;
    int currentPositionForWidget = 0;
    int widthestWidgetSize = 0;

    for (WidgetText& thisWidget : listOfButton)
    {
        sizeOfAllWidgets += thisWidget.hitbox().height + 20;

        if (thisWidget.hitbox().width > widthestWidgetSize)
        {
            widthestWidgetSize = thisWidget.hitbox().width;
        }
    }
    sizeOfAllWidgets -= 20;

    currentPositionForWidget = (HEIGHT_SCREEN / 2) - (sizeOfAllWidgets / 2) + 50;

    for (WidgetText& thisWidget : listOfButton)
    {
        thisWidget.setPosition({(WIDTH_SCREEN / 2) - (widthestWidgetSize / 2), currentPositionForWidget});
        currentPositionForWidget += thisWidget.hitbox().height + 20;
    }
}
