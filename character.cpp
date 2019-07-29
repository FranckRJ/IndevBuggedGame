#include "character.hpp"

Character::~Character()
{
    // vide
}

sf::Vector2i Character::getPosition()
{
    return position;
}

void Character::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
}

void Character::setPosition(int newX, int newY)
{
    setPosition(sf::Vector2i(newX, newY));
}

void Character::changePosition(int addX, int addY)
{
    setPosition(sf::Vector2i(position.x + addX, position.y + addY));
}

Direction Character::getCurrentDirection() const
{
    return currentDirection;
}

void Character::setCurrentDirection(const Direction& value)
{
    currentDirection = value;
}

sf::IntRect Character::getCollideBox()
{
    return sf::IntRect(position.x, position.y, sizeOfCollideBox.x, sizeOfCollideBox.y);
}

int Character::getSpeed() const
{
    return speed;
}

int Character::getJumpPower() const
{
    return jumpPower;
}

double Character::getCurrentVerticalVelocity() const
{
    return currentVerticalVelocity;
}

void Character::setCurrentVerticalVelocity(double value)
{
    currentVerticalVelocity = value;
}

bool Character::getCanJump() const
{
    return canJump;
}

void Character::setCanJump(bool value)
{
    canJump = value;
}

bool Character::getIsInJump() const
{
    return isInJump;
}

void Character::setIsInJump(bool value)
{
    isInJump = value;
}

bool Character::getCanMoveIntentionally() const
{
    return canMoveIntentionally;
}

void Character::setCanMoveIntentionally(bool newVal)
{
    canMoveIntentionally = newVal;
}

bool Character::getCanJumpIntentionally() const
{
    return canJumpIntentionally;
}

void Character::setCanJumpIntentionally(bool value)
{
    canJumpIntentionally = value;
}

bool Character::getIsDead() const
{
    return isDead;
}

void Character::setIsDead(bool newVal)
{
    isDead = newVal;
}

bool Character::getHasTriggeredFinishBlock() const
{
    return hasTriggeredFinishBlock;
}

void Character::setHasTriggeredFinishBlock(bool value)
{
    hasTriggeredFinishBlock = value;
}
