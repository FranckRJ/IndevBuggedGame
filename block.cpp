#include "block.hpp"
#include "global.hpp"

Block::Block(const BlockProperties& newProperties, const BlockSprite& newSpriteInfos)
    : properties(newProperties), spriteInfos(newSpriteInfos)
{
    sprite.setSize(sf::Vector2f(spriteInfos.size.x, spriteInfos.size.y));
    sprite.setFillColor(spriteInfos.color);
    setCollisionForVersion();
}

void Block::update()
{
    if (hasCheckedCollideLastFrame)
    {
        hasCheckedCollideLastFrame = false;
    }
    else
    {
        wasInCollideLastFrame = false;
    }
}

void Block::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Block::isCollidingWith(sf::FloatRect collideBox)
{
    hasCheckedCollideLastFrame = true;

    wasInCollideLastFrame = collision.hasCollided(collideBox, sf::FloatRect(position.x + spriteInfos.margin.x,
                                                                            position.y + spriteInfos.margin.y,
                                                                            spriteInfos.size.x, spriteInfos.size.y));

    return wasInCollideLastFrame;
}

sf::Vector2i Block::getPosAfterCollide(sf::FloatRect collideBox, Direction dir)
{
    return collision.getNewPosAfterCollide(collideBox,
                                           sf::FloatRect(position.x + spriteInfos.margin.x,
                                                         position.y + spriteInfos.margin.y, spriteInfos.size.x,
                                                         spriteInfos.size.y),
                                           dir);
}

const BlockProperties Block::getBlockInfo()
{
    return properties;
}

bool Block::getWasInCollideLastFrame()
{
    return wasInCollideLastFrame;
}

void Block::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
    sprite.setPosition(position.x + spriteInfos.margin.x, position.y + spriteInfos.margin.y);
}

void Block::setPosition(int newX, int newY)
{
    position = sf::Vector2i(newX, newY);
    sprite.setPosition(newX + spriteInfos.margin.x, newY + spriteInfos.margin.y);
}

void Block::setCollisionForVersion()
{
    collision.setFuncsForGameVersion(Global::versionOfGame);
}
