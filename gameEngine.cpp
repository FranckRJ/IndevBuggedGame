#include "gameEngine.hpp"
#include "global.hpp"
#include "messageManager.hpp"
#include "playState.hpp"
#include "screenTransitionState.hpp"

GameEngine::GameEngine(std::string nameOfLevel)
{
    view.setSize(WIDTH_SCREEN, HEIGHT_SCREEN);
    view.setCenter(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

    currentLevelName = nameOfLevel;
    LevelManager::loadLevelFromFile(infoForLevel, nameOfLevel);
    Global::versionOfGame = infoForLevel.initialGameVersion;
    player.setPosition(infoForLevel.playerStartPosition);
    updateGameVersion();
    player.update();

    // pour empecher le joueur de se deplacer lors de la premiere frame (affichage de message etc).
    player.setCanMoveIntentionally(false);
    player.setCanJumpIntentionally(false);
}

void GameEngine::update()
{
    player.applyHorizontalMove();
    checkCharacterInBorder(player);
    checkCharacterCollideWithBlock(player, player.getCurrentDirection(), true);

    player.applyVerticalMove();
    checkCharacterInBorder(player);
    checkCharacterCollideWithBlock(player, player.getVerticalDirection(), true);

    player.setCanMoveIntentionally(true);
    player.setCanJumpIntentionally(true);
    checkCharacterInBorder(player);
    checkCharacterCollideWithBlock(player, player.getCurrentDirection());
    setCameraToCharacter(player);
    checkCharacterCollideWithEvent(player);

    player.applyGravity(GRAVITY);
    player.update();

    listOfForegroundBlock.clear();
    for (int x = (view.getCenter().x - (WIDTH_SCREEN / 2)) / SIZE_BLOCK;
         x < (view.getCenter().x + (WIDTH_SCREEN / 2)) / SIZE_BLOCK; ++x)
    {
        for (int y = (view.getCenter().y - (HEIGHT_SCREEN / 2)) / SIZE_BLOCK;
             y < (view.getCenter().y + (HEIGHT_SCREEN / 2)) / SIZE_BLOCK; ++y)
        {
            auto block = infoForLevel.mapOfGame.find(Point(x, y));
            if (block != infoForLevel.mapOfGame.end())
            {
                block->second->update();
                if (block->second->getBlockInfo().isInForeground)
                {
                    listOfForegroundBlock.push_back(block->second.get());
                }
            }
        }
    }

    if (player.getHasTriggeredFinishBlock())
    {
        if (infoForLevel.nextLevelName.empty())
        {
            infoForLevel.nextLevelName = currentLevelName;
        }
        Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
            std::make_unique<PlayState>(infoForLevel.nextLevelName), sf::Color::Black, 25));
    }
    else if (player.getIsDead())
    {
        Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
            std::make_unique<PlayState>(currentLevelName), sf::Color::Black, 25));
    }
}

void GameEngine::draw(sf::RenderWindow& window)
{
    window.setView(view);

    for (int x = (view.getCenter().x - (WIDTH_SCREEN / 2)) / SIZE_BLOCK;
         x < (view.getCenter().x + (WIDTH_SCREEN / 2)) / SIZE_BLOCK; ++x)
    {
        for (int y = (view.getCenter().y - (HEIGHT_SCREEN / 2)) / SIZE_BLOCK;
             y < (view.getCenter().y + (HEIGHT_SCREEN / 2)) / SIZE_BLOCK; ++y)
        {
            auto block = infoForLevel.mapOfGame.find(Point(x, y));
            if (block != infoForLevel.mapOfGame.end())
            {
                block->second->draw(window);
            }
        }
    }

    player.draw(window);

    for (Block* thisBlock : listOfForegroundBlock)
    {
        thisBlock->draw(window);
    }
}

void GameEngine::setPlayerDirection(Direction dir)
{
    player.setCurrentDirection(dir);
}

void GameEngine::jumpPlayer(bool spaceWasPressedLastFrame)
{
    player.startJump(spaceWasPressedLastFrame);
}

void GameEngine::checkCharacterInBorder(Character& character)
{
    if (character.getPosition().x < infoForLevel.limitOfGame.left)
    {
        character.hasEnterInCollide(Direction::LEFT);
        character.setPosition(infoForLevel.limitOfGame.left, character.getPosition().y);
    }
    else if (character.getPosition().x + character.getCollideBox().width >
             infoForLevel.limitOfGame.left + infoForLevel.limitOfGame.width)
    {
        character.hasEnterInCollide(Direction::RIGHT);
        character.setPosition(infoForLevel.limitOfGame.left + infoForLevel.limitOfGame.width -
                                  character.getCollideBox().width,
                              character.getPosition().y);
    }

    if (character.getPosition().y < infoForLevel.limitOfGame.top)
    {
        character.hasEnterInCollide(Direction::UP);
        character.setPosition(character.getPosition().x, infoForLevel.limitOfGame.top);
    }
    else if (character.getPosition().y + character.getCollideBox().height >
             infoForLevel.limitOfGame.top + infoForLevel.limitOfGame.height)
    {
        character.hasEnterInCollide(Direction::DOWN);
        character.setPosition(character.getPosition().x, infoForLevel.limitOfGame.top +
                                                             infoForLevel.limitOfGame.height -
                                                             character.getCollideBox().height);
    }
}

void GameEngine::checkCharacterCollideWithBlock(Character& character, Direction dir, bool onlySolid)
{
    for (int x = character.getCollideBox().left / SIZE_BLOCK;
         x <= (character.getCollideBox().left + character.getCollideBox().width) / SIZE_BLOCK; ++x)
    {
        for (int y = character.getCollideBox().top / SIZE_BLOCK;
             y <= (character.getCollideBox().top + character.getCollideBox().height) / SIZE_BLOCK; ++y)
        {
            auto block = infoForLevel.mapOfGame.find(Point(x, y));

            if (block != infoForLevel.mapOfGame.end())
            {
                block->second->applyCollision(character, dir, onlySolid);
            }
        }
    }
}

void GameEngine::checkCharacterCollideWithEvent(Character& character)
{
    for (auto eventIte = infoForLevel.listOfEvent.begin(); eventIte != infoForLevel.listOfEvent.end();)
    {
        if ((*eventIte)->isCollideWith(character.getCollideBox()))
        {
            if ((*eventIte)->getEventInfo().isUpdateEvent)
            {
                Global::versionOfGame = (*eventIte)->getEventInfo().newVersion;

                updateGameVersion();
            }
            if ((*eventIte)->getEventInfo().isShowMessageEvent)
            {
                MessageManager::addMessageStateToStack("NORMAL_MESSAGE", (*eventIte)->getEventInfo().messageToShow);
                infoForLevel.listOfEvent.erase(eventIte++);
                break;
            }
            infoForLevel.listOfEvent.erase(eventIte++);
            continue;
        }
        ++eventIte;
    }
}

void GameEngine::setCameraToCharacter(Character& character)
{
    view.setCenter(character.getSpriteBox().left + character.getSpriteBox().width / 2,
                   character.getSpriteBox().top + character.getSpriteBox().height / 2);

    if (view.getCenter().x < infoForLevel.limitOfGame.left + (WIDTH_SCREEN / 2))
    {
        view.setCenter(infoForLevel.limitOfGame.left + (WIDTH_SCREEN / 2), view.getCenter().y);
    }
    else if (view.getCenter().x > infoForLevel.limitOfGame.left + infoForLevel.limitOfGame.width - (WIDTH_SCREEN / 2))
    {
        view.setCenter(infoForLevel.limitOfGame.left + infoForLevel.limitOfGame.width - (WIDTH_SCREEN / 2),
                       view.getCenter().y);
    }

    if (view.getCenter().y < infoForLevel.limitOfGame.top + (HEIGHT_SCREEN / 2))
    {
        view.setCenter(view.getCenter().x, infoForLevel.limitOfGame.top + (HEIGHT_SCREEN / 2));
    }
    else if (view.getCenter().y > infoForLevel.limitOfGame.top + infoForLevel.limitOfGame.height - (HEIGHT_SCREEN / 2))
    {
        view.setCenter(view.getCenter().x,
                       infoForLevel.limitOfGame.top + infoForLevel.limitOfGame.height - (HEIGHT_SCREEN / 2));
    }
}

void GameEngine::updateGameVersion()
{
    for (auto& thisBlock : infoForLevel.mapOfGame)
    {
        thisBlock.second->setCollisionForVersion();
    }

    player.setMovementForVersion();
}
