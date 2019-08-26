#include "mainMenuState.hpp"
#include "editLevelState.hpp"
#include "global.hpp"
#include "playState.hpp"
#include "screenTransitionState.hpp"

MainMenuState::MainMenuState()
{
    mNameOfGameText.setSize(60);
    mNameOfGameText.setMessage("Indev Bugged Game");
    mNameOfGameText.setFillColor(sf::Color::Green);
    mNameOfGameText.setPosition({25, 25});

    mListOfButton[0].setSize(40);
    mListOfButton[0].setMessage("Jouer");
    mListOfButton[0].setFillColor(sf::Color::Green);

    mListOfButton[1].setSize(40);
    mListOfButton[1].setMessage("Editer");
    mListOfButton[1].setFillColor(sf::Color::Green);

    mListOfButton[2].setSize(40);
    mListOfButton[2].setMessage("Rien");
    mListOfButton[2].setFillColor(sf::Color::Green);

    mListOfButton[3].setSize(40);
    mListOfButton[3].setMessage("Quitter");
    mListOfButton[3].setFillColor(sf::Color::Green);

    centerWidgetInList();

    mCursorText.setSize(50);
    mCursorText.setMessage(">");
    mCursorText.setFillColor(sf::Color::Green);
    mCursorText.setPosition({mListOfButton[mCurrentId].position().x - mCursorText.hitbox().width - 20, 0});

    mCursorText.setCentralVerticalPos(mListOfButton[mCurrentId].centralVerticalPos());
    mCursorText.setPositionToReach(mListOfButton[mCurrentId].centralVerticalPos());
}

// TODO split cette fonction
void MainMenuState::updateImpl(sf::RenderWindow& pWindow)
{
    auto event = sf::Event{};

    while (pWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            pWindow.close();
        }
        else if (event.type == sf::Event::KeyPressed && !mChoiceIsSelected)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                if (mCurrentId <= 0)
                {
                    mCurrentId = mListOfButton.size() - 1;
                }
                else
                {
                    --mCurrentId;
                }
                mCursorText.setPositionToReach(mListOfButton[mCurrentId].centralVerticalPos());
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                if (mCurrentId >= (mListOfButton.size() - 1))
                {
                    mCurrentId = 0;
                }
                else
                {
                    ++mCurrentId;
                }
                mCursorText.setPositionToReach(mListOfButton[mCurrentId].centralVerticalPos());
            }
            else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
            {
                if (mCurrentId == 3)
                {
                    pWindow.close();
                }
                else
                {
                    mListOfButton[mCurrentId].setNumberOfBlinkNeeded(3);
                    mChoiceIsSelected = true;
                }
            }
        }
    }

    if (mChoiceIsSelected && mListOfButton[mCurrentId].numberOfBlinkNeeded() == 0)
    {
        if (mCurrentId == 0)
        {
            Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
                std::make_unique<PlayState>("level1.txt"), sf::Color::Black, 25));
        }
        else if (mCurrentId == 1)
        {
            Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
                std::make_unique<EditLevelState>("level7.txt"), sf::Color::Black, 25));
        }
        else if (mCurrentId == 2)
        {
            Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
                std::make_unique<PlayState>("level6.txt"), sf::Color::Black, 25));
        }

        mChoiceIsSelected = false;
    }

    for (auto& thisWidget : mListOfButton)
    {
        thisWidget.update();
    }
    mNameOfGameText.update();
    mCursorText.update();
}

void MainMenuState::drawImpl(sf::RenderWindow& pWindow) const
{
    pWindow.setView(pWindow.getDefaultView());
    pWindow.clear(sf::Color::Black);
    mNameOfGameText.draw(pWindow);
    mCursorText.draw(pWindow);

    for (const auto& thisWidget : mListOfButton)
    {
        thisWidget.draw(pWindow);
    }
}

void MainMenuState::centerWidgetInList()
{
    auto sizeOfAllWidgets = 0;
    auto currentPositionForWidget = 0;
    auto widthestWidgetSize = 0;

    for (const auto& thisWidget : mListOfButton)
    {
        sizeOfAllWidgets += thisWidget.hitbox().height + 20;

        if (thisWidget.hitbox().width > widthestWidgetSize)
        {
            widthestWidgetSize = thisWidget.hitbox().width;
        }
    }
    sizeOfAllWidgets -= 20;

    currentPositionForWidget = (HEIGHT_SCREEN / 2) - (sizeOfAllWidgets / 2) + 50;

    for (auto& thisWidget : mListOfButton)
    {
        thisWidget.setPosition({(WIDTH_SCREEN / 2) - (widthestWidgetSize / 2), currentPositionForWidget});
        currentPositionForWidget += thisWidget.hitbox().height + 20;
    }
}
