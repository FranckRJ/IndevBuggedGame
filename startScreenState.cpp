#include "startScreenState.hpp"
#include "global.hpp"
#include "mainMenuState.hpp"
#include "screenTransitionState.hpp"

startScreenStateClass::startScreenStateClass()
{
    sf::Text finalMessage;
    finalMessage.setCharacterSize(80);
    finalMessage.setFont(global::font);
    finalMessage.setString("> start IBG.exe_");

    currentMessage.setCharacterSize(80);
    currentMessage.setFont(global::font);
    currentMessage.setFillColor(sf::Color::Green);
    currentMessage.setOrigin(0, static_cast<int>(finalMessage.getLocalBounds().top));
    currentMessage.setPosition((WIDTH_SCREEN / 2) - (finalMessage.getGlobalBounds().width / 2),
                               (HEIGHT_SCREEN / 2) - (finalMessage.getGlobalBounds().height / 2));

    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> _"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> "));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> _"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> "));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> _"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> s_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> st_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> sta_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> star_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start _"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start I_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IB_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG._"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.e_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.ex_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe_"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.5"));
    listOfInstructions.push_back(instructionStruct("SET_MESSAGE", "> start IBG.exe"));
    listOfInstructions.push_back(instructionStruct("WAIT", "0.1"));
}

void startScreenStateClass::update(sf::RenderWindow& window)
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
            if (event.key.code == sf::Keyboard::Space)
            {
                listOfInstructions.clear();
            }
        }
    }

    if (!listOfInstructions.empty())
    {
        if (listOfInstructions.front().typeOfInstruction == "SET_MESSAGE")
        {
            currentMessage.setString(listOfInstructions.front().infosForInstruction);
            listOfInstructions.pop_front();
        }
        else if (listOfInstructions.front().typeOfInstruction == "WAIT")
        {
            if (!isWaiting)
            {
                isWaiting = true;
                timer.restart();
            }

            if (timer.getElapsedTime().asSeconds() > std::stof(listOfInstructions.front().infosForInstruction))
            {
                isWaiting = false;
                listOfInstructions.pop_front();
            }
        }
    }

    if (listOfInstructions.empty())
    {
        global::activeGameStateStack->add(
            std::make_unique<screenTransitionStateClass>(std::make_unique<mainMenuStateClass>(), sf::Color::Black, 25));
    }
}

void startScreenStateClass::draw(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    window.clear(sf::Color::Black);
    window.draw(currentMessage);
}
