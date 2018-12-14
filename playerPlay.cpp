#include "playerPlay.hpp"
#include "movement1.hpp"
#include "global.hpp"

playerPlayClass::playerPlayClass()
{
    currentFrame = 0;
    infoForMove.speed = 5;
    infoForMove.jumpPower = -20;
    isDead = false;
    lastDir = RIGHT;
    infoForMove.currentVerticalVelocity = 0;
    infoForMove.canJump = true;
    infoForMove.isInJump = false;
    spriteDeformation = sf::Vector2f(0, 0);
    spriteDeformationNeeded = 0;
    sizeOfCollideBox = sf::Vector2i(40, 80);
    sprite.setSize(sf::Vector2f(40, 80));
    sprite.setFillColor(sf::Color::Blue);
    spriteVisor.setFillColor(sf::Color(0, 0, 150));
    setVisorForSprite();
    currentDir = NONE;
    setMovementForVersion();
}

void playerPlayClass::update()
{
    currentFrame = ((currentFrame + 1) % 64);
    currentDir = NONE;

    if(currentFrame % 2 == 0)
    {
        applySpriteDeformation();
    }

    particleMotor.update();
}

void playerPlayClass::draw(sf::RenderWindow& window)
{
    particleMotor.draw(window);
    window.draw(sprite);
    window.draw(spriteVisor);
}

bool playerPlayClass::applyMove()
{
    if(movement.get() != nullptr && currentDir != NONE)
    {
        position = movement->moveCharacterTo(infoForMove, currentDir, position);
        sprite.setPosition(position.x - spriteDeformation.x, position.y - spriteDeformation.y);
        setVisorForSprite();

        if(currentFrame % 8 == 0 && infoForMove.isInJump == false && infoForMove.currentVerticalVelocity < (GRAVITY * 2))
        {
            if(currentDir == RIGHT)
            {
                particleMotor.addParticle(sf::Vector2f(position.x, position.y + sizeOfCollideBox.y), -infoForMove.speed);
            }
            else if(currentDir == LEFT)
            {
                particleMotor.addParticle(sf::Vector2f(position.x + sizeOfCollideBox.x, position.y + sizeOfCollideBox.y), infoForMove.speed);
            }
        }

        if(currentDir != NONE)
        {
            lastDir = currentDir;
        }
    }

    return false;
}

bool playerPlayClass::applyVerticalMove()
{
    if(movement.get() != nullptr && infoForMove.currentVerticalVelocity != 0)
    {
        position = movement->applyGravity(infoForMove, position);
        sprite.setPosition(position.x - spriteDeformation.x, position.y - spriteDeformation.y);
        setVisorForSprite();
    }

    return false;
}

void playerPlayClass::applySpriteDeformation()
{
    if(spriteDeformationNeeded != 0)
    {
        if(spriteDeformationNeeded < 0)
        {
            moveSpriteDeformation(-1);
            ++spriteDeformationNeeded;
        }
    }
    else
    {
        if(spriteDeformation.x != 0)
        {
            if(spriteDeformation.x < 0)
            {
                moveSpriteDeformation(1);
            }
        }
    }

    sprite.setPosition(position.x - spriteDeformation.x, position.y - spriteDeformation.y);
    setVisorForSprite();
}

void playerPlayClass::moveSpriteDeformation(int amount)
{
    spriteDeformation.x += amount;
    spriteDeformation.y -= amount;
    sprite.setSize(sf::Vector2f(sprite.getSize().x + (amount * 2), sprite.getSize().y - (amount * 2)));
}

void playerPlayClass::hasEnterInCollide(direction dir)
{
    if(movement.get() != nullptr)
    {
        movement->enterInCollide(infoForMove, dir);
    }
}

void playerPlayClass::startJump()
{
    if(movement.get() != nullptr)
    {
        if(movement->startJump(infoForMove) == true)
        {
            if(spriteDeformationNeeded == 0 && spriteDeformation.x == 0)
            {
                spriteDeformationNeeded = -4;
            }
        }
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
    if(infoForMove.currentVerticalVelocity < 0)
    {
        return UP;
    }
    else if(infoForMove.currentVerticalVelocity > 0)
    {
        return DOWN;
    }
    else
    {
        return NONE;
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
    sprite.setPosition(position.x - spriteDeformation.x, position.y - spriteDeformation.y);
    setVisorForSprite();
}

void playerPlayClass::setPosition(int newX, int newY)
{
    position = sf::Vector2i(newX, newY);
    sprite.setPosition(newX - spriteDeformation.x, newY - spriteDeformation.y);
    setVisorForSprite();
}

void playerPlayClass::setMovementForVersion()
{
    if(global::versionOfGame >= 1)
    {
        if(global::versionOfGame < 2)
        {
            movement.reset(new movement1Class);
        }
    }
}

void playerPlayClass::setVisorForSprite()
{
    spriteVisor.setSize(sf::Vector2f(sprite.getSize().x / 2, 10));

    if(lastDir == RIGHT)
    {
        spriteVisor.setPosition(sprite.getPosition().x + (sprite.getSize().x / 2), sprite.getPosition().y + 10);
    }
    else if(lastDir == LEFT)
    {
        spriteVisor.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10);
    }
}
