#include "block.hpp"
#include "global.hpp"

Block::Block(const BlockProperties& pProperties, const BlockSprite& pSpriteInfos, BlockId pId)
    : mProperties{pProperties}, mSpriteInfos{pSpriteInfos}, mId{pId}
{
    mSprite.setSize(sf::Vector2f(mSpriteInfos.size.x, mSpriteInfos.size.y));
    mSprite.setFillColor(mSpriteInfos.color);
}

void Block::update()
{
    if (mHasCheckedCollideLastFrame)
    {
        mHasCheckedCollideLastFrame = false;
    }
    else
    {
        mWasInCollideLastFrame = false;
    }
}

void Block::draw(sf::RenderWindow& pWindow)
{
    pWindow.draw(mSprite);
}

sf::IntRect Block::collideBox() const
{
    return sf::IntRect{mPosition.x + mSpriteInfos.margin.x, mPosition.y + mSpriteInfos.margin.y, mSpriteInfos.size.x,
                       mSpriteInfos.size.y};
}

const BlockProperties Block::blockInfos() const
{
    return mProperties;
}

bool Block::wasInCollideLastFrame() const
{
    return mWasInCollideLastFrame;
}

void Block::setPosition(sf::Vector2i pPosition)
{
    mPosition = pPosition;
    mSprite.setPosition(mPosition.x + mSpriteInfos.margin.x, mPosition.y + mSpriteInfos.margin.y);
}

void Block::setCollisionForVersion(const VersionNumber& pVersionOfGame)
{
    mCollision.setFuncsForGameVersion(pVersionOfGame);
}

bool Block::applyCollision(Character& pCharacter, Direction pMovementDir, bool pOnlyPositionCheck)
{
    auto isColliding = mCollision.isCollidingBlock(pCharacter, *this, pMovementDir);

    if (pOnlyPositionCheck)
    {
        if (isColliding && mProperties.isSolid)
        {
            mCollision.replaceCharacterNearBlock(pCharacter, *this, pMovementDir);
            pCharacter.hasEnterInCollide(pMovementDir);
        }
    }
    else
    {
        if (isColliding && (mProperties.isTriggeredContinuously || !mWasInCollideLastFrame))
        {
            if (mProperties.isDeadlyToPlayer)
            {
                pCharacter.setStatus(Character::Status::isDead, true);
            }
            for (const auto& [effectStatus, effectValue] : mProperties.temporaryEffects)
            {
                pCharacter.setStatus(effectStatus, effectValue);
            }
            if (mProperties.affectCharacterMove != sf::Vector2i(0, 0))
            {
                pCharacter.addToListOfBlocksAffectingMove(mId);
            }
            if (mProperties.isFinishTrigger)
            {
                pCharacter.setStatus(Character::Status::hasTriggeredFinishBlock, true);
            }
        }
        mWasInCollideLastFrame = isColliding;
    }

    return isColliding;
}
