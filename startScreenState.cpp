#include <cstdlib>

#include "startScreenState.hpp"
#include "screenTransitionState.hpp"
#include "mainMenuState.hpp"
#include "global.hpp"

startScreenStateClass::startScreenStateClass()
{
    waiting = false;

    sf::Text baseMessage;
    baseMessage.setCharacterSize(80);
    baseMessage.setFont(global::font);
    baseMessage.setString("> start IBG.exe");

    messageToShow.setCharacterSize(80);
    messageToShow.setFont(global::font);
    messageToShow.setColor(sf::Color::Green);
    messageToShow.setOrigin(0, static_cast<int>(baseMessage.getLocalBounds().top));
    messageToShow.setPosition((WIDTH_SCREEN / 2) - (baseMessage.getGlobalBounds().width / 2), (HEIGHT_SCREEN / 2) - (baseMessage.getGlobalBounds().height / 2));

    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> _"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> "));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> _"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> "));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> _"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> s_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> st_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> sta_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> star_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start _"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start I_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IB_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG._"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.e_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.ex_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstruction.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstruction.push_back(instructionStruct("WAIT", "0.1"));
}

void startScreenStateClass::update(sf::RenderWindow& window)
{
    sf::Event event;

    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                listOfInstruction.clear();
            }
        }
    }

    if(listOfInstruction.front().typeOfInstruction == "SET_MESSAGE")
    {
        messageToShow.setString(listOfInstruction.front().infoForInstruction);
        listOfInstruction.pop_front();
    }
    else if(listOfInstruction.front().typeOfInstruction == "WAIT")
    {
        if(waiting == false)
        {
            waiting = true;
            timer.restart();
        }

        if(timer.getElapsedTime().asSeconds() > std::atof(listOfInstruction.front().infoForInstruction.c_str()))
        {
            waiting = false;
            listOfInstruction.pop_front();
        }
    }

    if(listOfInstruction.empty() == true)
    {
        global::activeGameStateStack->add(new screenTransitionStateClass(new mainMenuStateClass, sf::Color::Black, 25));
    }
}

void startScreenStateClass::draw(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black);
    window.draw(messageToShow);
}
