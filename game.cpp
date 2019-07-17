#include <ctime>

#include "game.hpp"
#include "startScreenState.hpp"
#include "blockManager.hpp"
#include "messageManager.hpp"
#include "particleManager.hpp"
#include "global.hpp"

gameClass::gameClass()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), "Indev Bugged Game", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(61);
    //window.setVerticalSyncEnabled(true);

    srand(time(nullptr));

    global::activeGameStateStack = &gameStateStack;
    global::font.loadFromFile("lucon.ttf");
    blockManagerClass::initialize();
    messageManagerClass::initialize();
    particleManagerClass::initialize();
    gameStateStack.set(new startScreenStateClass);
}

void gameClass::run()
{
    while(window.isOpen())
    {
        do
        {
            gameStateStack.setChange(false);
            gameStateStack.update(window);
        }
        while(gameStateStack.getChange());

        gameStateStack.draw(window);
        window.display();
    }
}
