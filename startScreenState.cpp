#include "startScreenState.hpp"
#include "global.hpp"
#include "mainMenuState.hpp"
#include "screenTransitionState.hpp"
#include "utls.hpp"

StartScreenState::StartScreenState()
{
    sf::Text finalMessage;
    finalMessage.setCharacterSize(80);
    finalMessage.setFont(Global::font);
    finalMessage.setString("> start IBG.exe_");

    mCurrentMessage.setCharacterSize(80);
    mCurrentMessage.setFont(Global::font);
    mCurrentMessage.setFillColor(sf::Color::Green);
    mCurrentMessage.setOrigin(0, utls::intFloor(finalMessage.getLocalBounds().top));
    mCurrentMessage.setPosition((WIDTH_SCREEN / 2) - (finalMessage.getGlobalBounds().width / 2),
                                (HEIGHT_SCREEN / 2) - (finalMessage.getGlobalBounds().height / 2));

    mListOfInstructions.push_back({"SET_MESSAGE", "> _"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> "});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> _"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> "});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> _"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> s_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> st_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> sta_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> star_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start _"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start I_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IB_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG._"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.e_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.ex_"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe_"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe_"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe_"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe_"});
    mListOfInstructions.push_back({"WAIT", "0.5"});
    mListOfInstructions.push_back({"SET_MESSAGE", "> start IBG.exe"});
    mListOfInstructions.push_back({"WAIT", "0.1"});
}

void StartScreenState::updateImpl(sf::RenderWindow& pWindow)
{
    auto event = sf::Event{};

    while (pWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            pWindow.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                mListOfInstructions.clear();
            }
        }
    }

    if (!mListOfInstructions.empty())
    {
        if (mListOfInstructions.front().typeOfInstruction == "SET_MESSAGE")
        {
            mCurrentMessage.setString(mListOfInstructions.front().infosForInstruction);
            mListOfInstructions.pop_front();
        }
        else if (mListOfInstructions.front().typeOfInstruction == "WAIT")
        {
            if (!mIsWaiting)
            {
                mIsWaiting = true;
                mTimer.restart();
            }

            if (mTimer.getElapsedTime().asSeconds() > std::stof(mListOfInstructions.front().infosForInstruction))
            {
                mIsWaiting = false;
                mListOfInstructions.pop_front();
            }
        }
    }

    if (mListOfInstructions.empty())
    {
        Global::activeGameStateStack->add(
            std::make_unique<ScreenTransitionState>(std::make_unique<MainMenuState>(), sf::Color::Black, 25));
    }
}

void StartScreenState::drawImpl(sf::RenderWindow& pWindow) const
{
    pWindow.setView(pWindow.getDefaultView());
    pWindow.clear(sf::Color::Black);
    pWindow.draw(mCurrentMessage);
}
