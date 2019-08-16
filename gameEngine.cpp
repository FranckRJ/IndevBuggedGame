#include "gameEngine.hpp"
#include "global.hpp"
#include "messageManager.hpp"
#include "playState.hpp"
#include "screenTransitionState.hpp"
#include "utls.hpp"

GameEngine::GameEngine(std::string pNameOfLevel)
{
    mView.setSize(WIDTH_SCREEN, HEIGHT_SCREEN);
    mView.setCenter(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

    mCurrentLevelName = pNameOfLevel;
    LevelManager::loadLevelFromFile(mInfoForLevel, pNameOfLevel);
    mVersionOfGame = mInfoForLevel.initialGameVersion;
    mPlayer.setPosition(mInfoForLevel.playerStartPosition);
    updateGameVersion();
    mPlayer.update();

    // pour empecher le joueur de se deplacer lors de la premiere frame (affichage de message etc).
    mPlayer.setStatus(Character::Status::canMoveIntentionally, false);
    mPlayer.setStatus(Character::Status::canJumpIntentionally, false);
}

void GameEngine::update()
{
    mPlayer.applyHorizontalMove();
    checkCharacterInBorder(mPlayer);
    checkCharacterCollideWithBlock(mPlayer, mPlayer.movedHorizontalDirection(), true);

    mPlayer.applyVerticalMove();
    checkCharacterInBorder(mPlayer);
    checkCharacterCollideWithBlock(mPlayer, mPlayer.movedVerticalDirection(), true);

    mPlayer.setStatus(Character::Status::canMoveIntentionally, true);
    mPlayer.setStatus(Character::Status::canJumpIntentionally, true);
    mPlayer.setStatus(Character::Status::isInFluid, false);
    mPlayer.resetListOfBlocksAffectingMove();
    checkCharacterInBorder(mPlayer);
    checkCharacterCollideWithBlock(mPlayer, mPlayer.movedHorizontalDirection());
    setCameraToCharacter(mPlayer);
    checkCharacterCollideWithEvent(mPlayer);

    mPlayer.applyGravity(GRAVITY);
    mPlayer.update();

    mListOfForegroundBlock.clear();
    for (auto x = int{utls::intFloor((mView.getCenter().x - (WIDTH_SCREEN / 2)) / SIZE_BLOCK)};
         x < (mView.getCenter().x + (WIDTH_SCREEN / 2)) / SIZE_BLOCK; ++x)
    {
        for (auto y = int{utls::intFloor((mView.getCenter().y - (HEIGHT_SCREEN / 2)) / SIZE_BLOCK)};
             y < (mView.getCenter().y + (HEIGHT_SCREEN / 2)) / SIZE_BLOCK; ++y)
        {
            auto block = mInfoForLevel.mapOfGame.find(Point(x, y));
            if (block != mInfoForLevel.mapOfGame.end())
            {
                block->second->update();
                if (block->second->blockInfos().isInForeground)
                {
                    mListOfForegroundBlock.push_back(block->second.get());
                }
            }
        }
    }

    if (mPlayer.hasStatus(Character::Status::hasTriggeredFinishBlock))
    {
        if (mInfoForLevel.nextLevelName.empty())
        {
            mInfoForLevel.nextLevelName = mCurrentLevelName;
        }
        Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
            std::make_unique<PlayState>(mInfoForLevel.nextLevelName), sf::Color::Black, 25));
    }
    else if (mPlayer.hasStatus(Character::Status::isDead))
    {
        Global::activeGameStateStack->add(std::make_unique<ScreenTransitionState>(
            std::make_unique<PlayState>(mCurrentLevelName), sf::Color::Black, 25));
    }
}

void GameEngine::draw(sf::RenderWindow& pWindow)
{
    pWindow.setView(mView);

    for (auto x = int{utls::intFloor((mView.getCenter().x - (WIDTH_SCREEN / 2)) / SIZE_BLOCK)};
         x < (mView.getCenter().x + (WIDTH_SCREEN / 2)) / SIZE_BLOCK; ++x)
    {
        for (auto y = int{utls::intFloor((mView.getCenter().y - (HEIGHT_SCREEN / 2)) / SIZE_BLOCK)};
             y < (mView.getCenter().y + (HEIGHT_SCREEN / 2)) / SIZE_BLOCK; ++y)
        {
            auto block = mInfoForLevel.mapOfGame.find(Point(x, y));

            if (block != mInfoForLevel.mapOfGame.end())
            {
                block->second->draw(pWindow);
            }
        }
    }

    mPlayer.draw(pWindow);

    for (auto& block : mListOfForegroundBlock)
    {
        block->draw(pWindow);
    }
}

void GameEngine::setPlayerDirection(Direction pDirection)
{
    mPlayer.setMovingDirection(pDirection);
}

void GameEngine::jumpPlayer(bool pSpaceWasPressedLastFrame)
{
    mPlayer.startJump(pSpaceWasPressedLastFrame);
}

void GameEngine::checkCharacterInBorder(Character& pCharacter)
{
    auto oldPosition = pCharacter.position();
    auto newPosition = sf::Vector2i{utls::coerceIn(oldPosition.x, mInfoForLevel.limitOfGame.left,
                                                   mInfoForLevel.limitOfGame.left + mInfoForLevel.limitOfGame.width -
                                                       pCharacter.collideBox().width),
                                    utls::coerceIn(oldPosition.y, mInfoForLevel.limitOfGame.top,
                                                   mInfoForLevel.limitOfGame.top + mInfoForLevel.limitOfGame.height -
                                                       pCharacter.collideBox().height)};

    if (newPosition.x > oldPosition.x)
    {
        pCharacter.hasEnterInCollide(Direction::LEFT);
    }
    else if (newPosition.x < oldPosition.x)
    {
        pCharacter.hasEnterInCollide(Direction::RIGHT);
    }

    if (newPosition.y > oldPosition.y)
    {
        pCharacter.hasEnterInCollide(Direction::UP);
    }
    else if (newPosition.y < oldPosition.y)
    {
        pCharacter.hasEnterInCollide(Direction::DOWN);
    }

    pCharacter.setPosition(newPosition);
}

void GameEngine::checkCharacterCollideWithBlock(Character& pCharacter, Direction pDirection, bool pOnlySolid)
{
    for (auto x = int{pCharacter.collideBox().left / SIZE_BLOCK};
         x <= (pCharacter.collideBox().left + pCharacter.collideBox().width) / SIZE_BLOCK; ++x)
    {
        for (auto y = int{pCharacter.collideBox().top / SIZE_BLOCK};
             y <= (pCharacter.collideBox().top + pCharacter.collideBox().height) / SIZE_BLOCK; ++y)
        {
            auto block = mInfoForLevel.mapOfGame.find({x, y});

            if (block != mInfoForLevel.mapOfGame.end())
            {
                block->second->applyCollision(pCharacter, pDirection, pOnlySolid);
            }
        }
    }
}

void GameEngine::checkCharacterCollideWithEvent(Character& pCharacter)
{
    for (auto eventIte = mInfoForLevel.listOfEvent.begin(); eventIte != mInfoForLevel.listOfEvent.end();)
    {
        if ((*eventIte)->isCollideWith(pCharacter.collideBox()))
        {
            if ((*eventIte)->getEventInfo().isUpdateEvent)
            {
                mVersionOfGame = (*eventIte)->getEventInfo().newVersion;

                updateGameVersion();
            }
            if ((*eventIte)->getEventInfo().isShowMessageEvent)
            {
                MessageManager::addMessageStateToStack("NORMAL_MESSAGE", (*eventIte)->getEventInfo().messageToShow);
                mInfoForLevel.listOfEvent.erase(eventIte++);
                break;
            }
            mInfoForLevel.listOfEvent.erase(eventIte++);
            continue;
        }
        ++eventIte;
    }
}

void GameEngine::setCameraToCharacter(Character& pCharacter)
{
    mView.setCenter(
        utls::coerceIn(utls::intFloor(pCharacter.spriteBox().left + pCharacter.spriteBox().width / 2),
                       mInfoForLevel.limitOfGame.left + (WIDTH_SCREEN / 2),
                       mInfoForLevel.limitOfGame.left + mInfoForLevel.limitOfGame.width - (WIDTH_SCREEN / 2)),
        utls::coerceIn(utls::intFloor(pCharacter.spriteBox().top + pCharacter.spriteBox().height / 2),
                       mInfoForLevel.limitOfGame.top + (HEIGHT_SCREEN / 2),
                       mInfoForLevel.limitOfGame.top + mInfoForLevel.limitOfGame.height - (HEIGHT_SCREEN / 2)));
}

void GameEngine::updateGameVersion()
{
    for (auto& [position, block] : mInfoForLevel.mapOfGame)
    {
        block->setCollisionForVersion(mVersionOfGame);
    }

    mPlayer.setMovementForVersion(mVersionOfGame);
}
