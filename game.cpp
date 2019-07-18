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
    global::font.loadFromFile("resources/lucon.ttf");
    blockManagerClass::initialize();
    messageManagerClass::initialize();
    particleManagerClass::initialize();
    gameStateStack.set(std::make_unique<startScreenStateClass>());
}

void gameClass::run()
{
    while(window.isOpen())
    {
        do
        {
            gameStateStack.resetStackHasChanged();
            gameStateStack.update(window);
        }
        while(gameStateStack.getStackHasChanged());

        gameStateStack.draw(window);
        window.display();
    }
}
