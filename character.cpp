#include "character.hpp"

Character::~Character()
{
    // vide
}

bool Character::getIsDead()
{
    return isDead;
}

sf::FloatRect Character::getCollideBox()
{
    return sf::FloatRect(position.x, position.y, sizeOfCollideBox.x, sizeOfCollideBox.y);
}

sf::Vector2i Character::getPosition()
{
    return position;
}

void Character::setCanMoveIntentionally(bool newVal)
{
    infoForMove.canMoveIntentionally = newVal;
}

void Character::setIsDead(bool newVal)
{
    isDead = newVal;
}

void Character::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
}

void Character::setPosition(int newX, int newY)
{
    setPosition(sf::Vector2i(newX, newY));
}
