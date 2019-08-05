#include <ctime>

#include "blockManager.hpp"
#include "game.hpp"
#include "global.hpp"
#include "messageManager.hpp"
#include "particleManager.hpp"
#include "startScreenState.hpp"

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), "Indev Bugged Game",
                  sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(61);
    // window.setVerticalSyncEnabled(true);

    srand(time(nullptr));

    Global::activeGameStateStack = &gameStateStack;
    Global::font.loadFromFile("resources/lucon.ttf");
    BlockManager::initialize();
    MessageManager::initialize();
    ParticleManager::initialize();
    gameStateStack.set(std::make_unique<StartScreenState>());
}

void Game::run()
{
    while (window.isOpen())
    {
        do
        {
            gameStateStack.resetStackHasChanged();
            gameStateStack.update(window);
        } while (gameStateStack.stackHasChanged());

        gameStateStack.draw(window);
        window.display();
    }
}
