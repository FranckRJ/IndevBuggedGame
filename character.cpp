#include "character.hpp"

characterClass::~characterClass()
{
    // vide
}

bool characterClass::getIsDead()
{
    return isDead;
}

sf::FloatRect characterClass::getCollideBox()
{
    return sf::FloatRect(position.x, position.y, sizeOfCollideBox.x, sizeOfCollideBox.y);
}

sf::Vector2i characterClass::getPosition()
{
    return position;
}

void characterClass::setCanMoveIntentionally(bool newVal)
{
    infoForMove.canMoveIntentionally = newVal;
}

void characterClass::setIsDead(bool newVal)
{
    isDead = newVal;
}

void characterClass::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
}

void characterClass::setPosition(int newX, int newY)
{
    setPosition(sf::Vector2i(newX, newY));
}
