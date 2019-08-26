#include "character.hpp"

void Character::update()
{
    updateImpl();
}

void Character::draw(sf::RenderWindow& pWindow) const
{
    drawImpl(pWindow);
}

Direction Character::movingDirection() const
{
    return movingDirectionImpl();
}

Direction Character::movedHorizontalDirection() const
{
    return movedHorizontalDirectionImpl();
}

Direction Character::movedVerticalDirection() const
{
    return movedVerticalDirectionImpl();
}

void Character::setMovingDirection(Direction pDirection)
{
    setMovingDirectionImpl(pDirection);
}

void Character::setMovedHorizontalDirection(Direction pDirection)
{
    setMovedHorizontalDirectionImpl(pDirection);
}

void Character::setMovedVerticalDirection(Direction pDirection)
{
    setMovedVerticalDirectionImpl(pDirection);
}

sf::FloatRect Character::spriteBox() const
{
    return spriteBoxImpl();
}

sf::IntRect Character::collideBox() const
{
    return collideBoxImpl();
}

sf::Vector2i Character::position() const
{
    return positionImpl();
}

void Character::setPosition(sf::Vector2i pPosition)
{
    setPositionImpl(pPosition);
}

void Character::changePosition(sf::Vector2i pChangeToApply)
{
    changePositionImpl(pChangeToApply);
}

double Character::verticalVelocity() const
{
    return verticalVelocityImpl();
}

void Character::setVerticalVelocity(double pVerticalVelocity)
{
    setVerticalVelocityImpl(pVerticalVelocity);
}

bool Character::canJump() const
{
    return canJumpImpl();
}

bool Character::isInJump() const
{
    return isInJumpImpl();
}

void Character::setCanJump(bool pCanJump)
{
    setCanJumpImpl(pCanJump);
}

void Character::setIsInJump(bool pIsInJump)
{
    setIsInJumpImpl(pIsInJump);
}

bool Character::hasStatus(Character::Status pStatus) const
{
    return hasStatusImpl(pStatus);
}

void Character::setStatus(Character::Status pStatus, bool pValue)
{
    setStatusImpl(pStatus, pValue);
}

void Character::resetAllStatus()
{
    resetAllStatusImpl();
}

const std::set<BlockId> Character::listOfBlocksAffectingMove() const
{
    return listOfBlocksAffectingMoveImpl();
}

void Character::addToListOfBlocksAffectingMove(BlockId pBlock)
{
    addToListOfBlocksAffectingMoveImpl(pBlock);
}

void Character::resetListOfBlocksAffectingMove()
{
    resetListOfBlocksAffectingMoveImpl();
}

int Character::speed() const
{
    return speedImpl();
}

int Character::jumpPower() const
{
    return jumpPowerImpl();
}

void Character::hasEnterInCollide(Direction pDirection)
{
    hasEnterInCollideImpl(pDirection);
}

CharacterImpl::CharacterImpl(int pSpeed, int pJumpPower) : mSpeed{pSpeed}, mJumpPower{pJumpPower}
{
}

Direction CharacterImpl::movingDirectionImpl() const
{
    return mMovingDirection;
}

Direction CharacterImpl::movedHorizontalDirectionImpl() const
{
    return mMovedHorizontalDirection;
}

Direction CharacterImpl::movedVerticalDirectionImpl() const
{
    return mMovedVerticalDirection;
}

void CharacterImpl::setMovingDirectionImpl(Direction pDirection)
{
    mMovingDirection = pDirection;
}

void CharacterImpl::setMovedHorizontalDirectionImpl(Direction pDirection)
{
    mMovedHorizontalDirection = pDirection;
}

void CharacterImpl::setMovedVerticalDirectionImpl(Direction pDirection)
{
    mMovedVerticalDirection = pDirection;
}

sf::Vector2i CharacterImpl::positionImpl() const
{
    return mPosition;
}

void CharacterImpl::setPositionImpl(sf::Vector2i pPosition)
{
    mPosition = pPosition;
}

void CharacterImpl::changePositionImpl(sf::Vector2i pChangeToApply)
{
    mPosition += pChangeToApply;
}

double CharacterImpl::verticalVelocityImpl() const
{
    return mVerticalVelocity;
}

void CharacterImpl::setVerticalVelocityImpl(double pVerticalVelocity)
{
    mVerticalVelocity = pVerticalVelocity;
}

bool CharacterImpl::canJumpImpl() const
{
    return mCanJump;
}

bool CharacterImpl::isInJumpImpl() const
{
    return mIsInJump;
}

void CharacterImpl::setCanJumpImpl(bool pCanJump)
{
    mCanJump = pCanJump;
}

void CharacterImpl::setIsInJumpImpl(bool pIsInJump)
{
    mIsInJump = pIsInJump;
}

bool CharacterImpl::hasStatusImpl(Status pStatus) const
{
    return mListOfStatus.count(pStatus) > 0;
}

void CharacterImpl::setStatusImpl(Status pStatus, bool pValue)
{
    if (pValue)
    {
        mListOfStatus.emplace(pStatus);
    }
    else
    {
        mListOfStatus.erase(pStatus);
    }
}

void CharacterImpl::resetAllStatusImpl()
{
    mListOfStatus.clear();
}

const std::set<BlockId> CharacterImpl::listOfBlocksAffectingMoveImpl() const
{
    return mListOfBlocksAffectingMove;
}

void CharacterImpl::addToListOfBlocksAffectingMoveImpl(BlockId pBlock)
{
    mListOfBlocksAffectingMove.emplace(pBlock);
}

void CharacterImpl::resetListOfBlocksAffectingMoveImpl()
{
    mListOfBlocksAffectingMove.clear();
}

int CharacterImpl::speedImpl() const
{
    return mSpeed;
}

int CharacterImpl::jumpPowerImpl() const
{
    return mJumpPower;
}
