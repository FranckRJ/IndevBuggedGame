#include "block.hpp"
#include "collision1.hpp"
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

bool blockClass::isCollideWith(sf::FloatRect collideBox, direction dir)
{
    collideCheckLastFrame = true;

    if (collision.get() != nullptr)
    {
        auto type = typeOfBlock.typeOfColli.find(COLLI_ALL);

        if (type != typeOfBlock.typeOfColli.end())
        {
            oldCollide = collision->isColliAll(type->second, collideBox,
                                               sf::FloatRect(position.x + typeOfBlock.spaceOfBlock.x,
                                                             position.y + typeOfBlock.spaceOfBlock.y,
                                                             typeOfBlock.sizeOfBlock.x, typeOfBlock.sizeOfBlock.y));
        }
        else
        {
            // auto lastType = typeOfBlock.typeOfColli.find(dir);

            switch (dir)
            {
                case LEFT:
                {
                    break;
                }
                case UP:
                {
                    break;
                }
                case RIGHT:
                {
                    break;
                }
                case DOWN:
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    return oldCollide;
}

sf::Vector2i blockClass::getNewPosOf(sf::FloatRect collideBox, direction dir)
{
    if (collision.get() != nullptr)
    {
        auto type = typeOfBlock.typeOfColli.find(COLLI_ALL);

        if (type != typeOfBlock.typeOfColli.end())
        {
            return collision->getNewPosColliAll(type->second, collideBox,
                                                sf::FloatRect(position.x + typeOfBlock.spaceOfBlock.x,
                                                              position.y + typeOfBlock.spaceOfBlock.y,
                                                              typeOfBlock.sizeOfBlock.x, typeOfBlock.sizeOfBlock.y),
                                                dir);
        }
        else
        {
            // auto lastType = typeOfBlock.typeOfColli.find(dir);

            switch (dir)
            {
                case LEFT:
                {
                    break;
                }
                case UP:
                {
                    break;
                }
                case RIGHT:
                {
                    break;
                }
                case DOWN:
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    return sf::Vector2i(collideBox.left, collideBox.top);
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
    if (global::versionOfGame >= "1.0"_vn)
    {
        if (global::versionOfGame < "2.0"_vn)
        {
            collision.reset(new collision1Class);
        }
    }
}
