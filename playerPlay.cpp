#include "playerPlay.hpp"
#include "global.hpp"
#include "utilities.hpp"

playerPlayClass::playerPlayClass()
{
    infoForMove.speed = 5;
    infoForMove.jumpPower = -20;
    infoForMove.currentVerticalVelocity = 0;
    infoForMove.canJump = true;
    infoForMove.canMoveIntentionally = true;
    infoForMove.isInJump = false;
    spriteSizeDeformation = sf::Vector2i(0, 0);
    baseSpriteSize = sf::Vector2i(40, 80);
    sizeOfCollideBox = baseSpriteSize;
    sprite.setFillColor(sf::Color::Blue);
    spriteVisor.setFillColor(sf::Color(0, 0, 150));
    setMovementForVersion();
}

void playerPlayClass::update()
{
    currentFrame = ((currentFrame + 1) % 64);
    currentDir = direction::NONE;

    if (currentFrame % 2 == 0)
    {
        applySpriteDeformation();
    }

    updateSpriteShape();
    particleMotor.update();
}

void playerPlayClass::draw(sf::RenderWindow& window)
{
    particleMotor.draw(window);
    window.draw(sprite);
    window.draw(spriteVisor);
}

void playerPlayClass::updateSpriteShape()
{
    if (spriteSizeDeformation.y < 0)
    {
        sprite.setPosition(position.x - (spriteSizeDeformation.x / 2), position.y - spriteSizeDeformation.y);
    }
    else
    {
        sprite.setPosition(position.x - (spriteSizeDeformation.x / 2), position.y);
    }
    sprite.setSize(
        sf::Vector2f(baseSpriteSize.x + spriteSizeDeformation.x, baseSpriteSize.y + spriteSizeDeformation.y));
    setVisorForSprite();
}

bool playerPlayClass::applyMove()
{
    if (infoForMove.canMoveIntentionally && currentDir != direction::NONE)
    {
        position = movement.moveCharacterTo(infoForMove, currentDir, position);

        if (currentFrame % 8 == 0 && !(infoForMove.isInJump) && infoForMove.currentVerticalVelocity < (GRAVITY * 2))
        {
            if (currentDir == direction::RIGHT)
            {
                particleMotor.addParticle(sf::Vector2f(position.x, position.y + sizeOfCollideBox.y),
                                          -infoForMove.speed);
            }
            else if (currentDir == direction::LEFT)
            {
                particleMotor.addParticle(
                    sf::Vector2f(position.x + sizeOfCollideBox.x, position.y + sizeOfCollideBox.y), infoForMove.speed);
            }
        }

        if (currentDir != direction::NONE)
        {
            lastDir = currentDir;
        }
    }

    return false;
}

bool playerPlayClass::applyVerticalMove()
{
    if (!utilitiesClass::doubleIsNear(infoForMove.currentVerticalVelocity, 0.0))
    {
        position = movement.applyGravity(infoForMove, position);
    }

    return false;
}

void playerPlayClass::applySpriteDeformation()
{
    if (spriteWidthDeformationNeeded != 0)
    {
        if (spriteWidthDeformationNeeded < 0)
        {
            if (!moveSpriteWidthDeformation(-2))
            {
                spriteWidthDeformationNeeded = 0;
            }
            else
            {
                ++spriteWidthDeformationNeeded;
            }
        }
        else
        {
            if (!moveSpriteWidthDeformation(2))
            {
                spriteWidthDeformationNeeded = 0;
            }
            else
            {
                --spriteWidthDeformationNeeded;
            }
        }
    }
    else
    {
        if (spriteSizeDeformation.x != 0)
        {
            if (spriteSizeDeformation.x < 0)
            {
                moveSpriteWidthDeformation(2);
            }
            else
            {
                moveSpriteWidthDeformation(-2);
            }
        }
    }
}

bool playerPlayClass::moveSpriteWidthDeformation(int amount)
{
    bool hasMovedFully = true;

    spriteSizeDeformation.x += amount;
    if (spriteSizeDeformation.x > 10)
    {
        spriteSizeDeformation.x = 10;
        hasMovedFully = false;
    }
    else if (spriteSizeDeformation.x < -10)
    {
        spriteSizeDeformation.x = -10;
        hasMovedFully = false;
    }
    spriteSizeDeformation.y -= amount;
    if (spriteSizeDeformation.y > 10)
    {
        spriteSizeDeformation.y = 10;
        hasMovedFully = false;
    }
    else if (spriteSizeDeformation.y < -10)
    {
        spriteSizeDeformation.y = -10;
        hasMovedFully = false;
    }
    return hasMovedFully;
}

void playerPlayClass::hasEnterInCollide(direction dir)
{
    if (dir == direction::DOWN)
    {
        if (infoForMove.currentVerticalVelocity > 64)
        {
            spriteWidthDeformationNeeded += 5;
        }
        else if (infoForMove.currentVerticalVelocity > 32)
        {
            spriteWidthDeformationNeeded += 4;
        }
        else if (infoForMove.currentVerticalVelocity > 16)
        {
            spriteWidthDeformationNeeded += 3;
        }
        else if (infoForMove.currentVerticalVelocity > 8)
        {
            spriteWidthDeformationNeeded += 2;
        }
        else if (infoForMove.currentVerticalVelocity > 4)
        {
            spriteWidthDeformationNeeded += 1;
        }
    }
    else if (dir == direction::UP)
    {
        spriteWidthDeformationNeeded = 0;
    }
    movement.enterInCollide(infoForMove, dir);
}

void playerPlayClass::startJump()
{
    if (movement.startJump(infoForMove))
    {
        spriteWidthDeformationNeeded -= 4;
    }
}

void playerPlayClass::attractTo(sf::Vector2i thisDirection)
{
    infoForMove.currentVerticalVelocity += thisDirection.y;
}

bool playerPlayClass::getIsDead()
{
    return isDead;
}

sf::FloatRect playerPlayClass::getSpriteBox()
{
    return sprite.getGlobalBounds();
}

sf::FloatRect playerPlayClass::getCollideBox()
{
    return sf::FloatRect(position.x, position.y, sizeOfCollideBox.x, sizeOfCollideBox.y);
}

sf::Vector2i playerPlayClass::getPosition()
{
    return position;
}

direction playerPlayClass::getDirection()
{
    return currentDir;
}

direction playerPlayClass::getVerticalDirection()
{
    if (infoForMove.currentVerticalVelocity < 0)
    {
        return direction::UP;
    }
    else if (infoForMove.currentVerticalVelocity > 0)
    {
        return direction::DOWN;
    }
    else
    {
        return direction::NONE;
    }
}

void playerPlayClass::setIsDead(bool newVal)
{
    isDead = newVal;
}

void playerPlayClass::setMoveTo(direction dir)
{
    currentDir = dir;
}

void playerPlayClass::setPosition(sf::Vector2i newPosition)
{
    position = newPosition;
}

void playerPlayClass::setPosition(int newX, int newY)
{
    setPosition(sf::Vector2i(newX, newY));
}

void playerPlayClass::setMovementForVersion()
{
    movement.setFuncsForGameVersion(global::versionOfGame);
}

void playerPlayClass::setVisorForSprite()
{
    spriteVisor.setSize(sf::Vector2f(sprite.getSize().x / 2, 10));

    if (lastDir == direction::RIGHT)
    {
        spriteVisor.setPosition(sprite.getPosition().x + (sprite.getSize().x / 2), sprite.getPosition().y + 10);
    }
    else if (lastDir == direction::LEFT)
    {
        spriteVisor.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10);
    }
}
