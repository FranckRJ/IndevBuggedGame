#include "block.hpp"
#include "global.hpp"

blockClass::blockClass()
{
    oldCollide = false;
    collideCheckLastFrame = false;
}

blockClass::blockClass(blockInfo newInfoForBlock, blockType newTypeOfBlock) : blockClass()
{
    infoForBlock = newInfoForBlock;
    typeOfBlock = newTypeOfBlock;

    sprite.setSize(sf::Vector2f(typeOfBlock.sizeOfBlock.x, typeOfBlock.sizeOfBlock.y));
    sprite.setFillColor(typeOfBlock.colorOfBlock);
    setCollisionForVersion();
}

void blockClass::update()
{
    if (collideCheckLastFrame)
    {
        collideCheckLastFrame = false;
    }
    else
    {
        oldCollide = false;
    }
}

void blockClass::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool blockClass::isCollideWith(sf::FloatRect collideBox)
{
    collideCheckLastFrame = true;

    oldCollide = collision.hasCollided(collideBox, sf::FloatRect(position.x + typeOfBlock.spaceOfBlock.x,
                                                                 position.y + typeOfBlock.spaceOfBlock.y,
                                                                 typeOfBlock.sizeOfBlock.x, typeOfBlock.sizeOfBlock.y));

    return oldCollide;
}

sf::Vector2i blockClass::getNewPosOf(sf::FloatRect collideBox, direction dir)
{
    return collision.getNewPosAfterCollide(collideBox,
                                           sf::FloatRect(position.x + typeOfBlock.spaceOfBlock.x,
                                                         position.y + typeOfBlock.spaceOfBlock.y,
                                                         typeOfBlock.sizeOfBlock.x, typeOfBlock.sizeOfBlock.y),
                                           dir);
}

const blockInfo blockClass::getBlockInfo()
{
    return infoForBlock;
}

bool blockClass::getOldCollide()
{
    return oldCollide;
}

void blockClass::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
    sprite.setPosition(position.x + typeOfBlock.spaceOfBlock.x, position.y + typeOfBlock.spaceOfBlock.y);
}

void blockClass::setPosition(int newX, int newY)
{
    position = sf::Vector2i(newX, newY);
    sprite.setPosition(newX + typeOfBlock.spaceOfBlock.x, newY + typeOfBlock.spaceOfBlock.y);
}

void blockClass::setCollisionForVersion()
{
    collision.setFuncsForGameVersion(global::versionOfGame);
}
