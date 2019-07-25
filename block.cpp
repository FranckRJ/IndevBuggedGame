#include "block.hpp"
#include "global.hpp"

blockClass::blockClass()
{
    wasInCollideLastFrame = false;
    hasCheckedCollideLastFrame = false;
}

blockClass::blockClass(blockProperties newProperties, blockSprite newSpriteInfos) : blockClass()
{
    properties = newProperties;
    spriteInfos = newSpriteInfos;

    sprite.setSize(sf::Vector2f(spriteInfos.size.x, spriteInfos.size.y));
    sprite.setFillColor(spriteInfos.color);
    setCollisionForVersion();
}

void blockClass::update()
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

void blockClass::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool blockClass::isCollideWith(sf::FloatRect collideBox)
{
    hasCheckedCollideLastFrame = true;

    wasInCollideLastFrame = collision.hasCollided(collideBox, sf::FloatRect(position.x + spriteInfos.margin.x,
                                                                            position.y + spriteInfos.margin.y,
                                                                            spriteInfos.size.x, spriteInfos.size.y));

    return wasInCollideLastFrame;
}

sf::Vector2i blockClass::getNewPosOf(sf::FloatRect collideBox, direction dir)
{
    return collision.getNewPosAfterCollide(collideBox,
                                           sf::FloatRect(position.x + spriteInfos.margin.x,
                                                         position.y + spriteInfos.margin.y, spriteInfos.size.x,
                                                         spriteInfos.size.y),
                                           dir);
}

const blockProperties blockClass::getBlockInfo()
{
    return properties;
}

bool blockClass::getWasInCollideLastFrame()
{
    return wasInCollideLastFrame;
}

void blockClass::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
    sprite.setPosition(position.x + spriteInfos.margin.x, position.y + spriteInfos.margin.y);
}

void blockClass::setPosition(int newX, int newY)
{
    position = sf::Vector2i(newX, newY);
    sprite.setPosition(newX + spriteInfos.margin.x, newY + spriteInfos.margin.y);
}

void blockClass::setCollisionForVersion()
{
    collision.setFuncsForGameVersion(global::versionOfGame);
}
