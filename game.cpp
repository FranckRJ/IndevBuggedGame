#include "game.hpp"
#include "blockManager.hpp"
#include "global.hpp"
#include "messageManager.hpp"
#include "particleManager.hpp"
#include "startScreenState.hpp"
#include "utls.hpp"

Game::Game()
{
    auto settings = sf::ContextSettings{};

    settings.antialiasingLevel = 8;
    mWindow.create(sf::VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), "Indev Bugged Game",
                   sf::Style::Titlebar | sf::Style::Close, settings);
    mWindow.setFramerateLimit(61);
    // mWindow.setVerticalSyncEnabled(true);

    Global::activeGameStateStack = &mGameStateStack;
    Global::font.loadFromFile("resources/lucon.ttf");
    BlockManager::initialize();
    MessageManager::initialize();
    ParticleManager::initialize();
    mGameStateStack.set(std::make_unique<StartScreenState>());
}

void Game::run()
{
    while (mWindow.isOpen())
    {
        do
        {
            mGameStateStack.resetStackHasChanged();
            mGameStateStack.update(mWindow);
        } while (mGameStateStack.stackHasChanged());

        mGameStateStack.draw(mWindow);
        mWindow.display();
    }
}
