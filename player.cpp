#include "player.hpp"
#include "global.hpp"
#include "utilities.hpp"

Player::Player()
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

void Player::update()
{
    currentFrame = ((currentFrame + 1) % 64);
    currentDir = Direction::NONE;

    if (currentFrame % 2 == 0)
    {
        applySpriteDeformation();
    }

    updateSpriteShape();
    particleMotor.update();
}

void Player::draw(sf::RenderWindow& window)
{
    particleMotor.draw(window);
    window.draw(sprite);
    window.draw(spriteVisor);
}

void Player::updateSpriteShape()
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

bool Player::applyMove()
{
    if (infoForMove.canMoveIntentionally && currentDir != Direction::NONE)
    {
        position = movement.moveCharacterTo(infoForMove, currentDir, position);

        if (currentFrame % 8 == 0 && !(infoForMove.isInJump) && infoForMove.currentVerticalVelocity < (GRAVITY * 2))
        {
            if (currentDir == Direction::RIGHT)
            {
                particleMotor.addParticle(sf::Vector2f(position.x, position.y + sizeOfCollideBox.y),
                                          -infoForMove.speed);
            }
            else if (currentDir == Direction::LEFT)
            {
                particleMotor.addParticle(
                    sf::Vector2f(position.x + sizeOfCollideBox.x, position.y + sizeOfCollideBox.y), infoForMove.speed);
            }
        }

        if (currentDir != Direction::NONE)
        {
            lastDir = currentDir;
        }
    }

    return false;
}

bool Player::applyVerticalMove()
{
    if (!Utilities::doubleIsNear(infoForMove.currentVerticalVelocity, 0.0))
    {
        position = movement.applyGravity(infoForMove, position);
    }

    return false;
}

void Player::applySpriteDeformation()
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

bool Player::moveSpriteWidthDeformation(int amount)
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

void Player::hasEnterInCollide(Direction dir)
{
    if (dir == Direction::DOWN)
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
    else if (dir == Direction::UP)
    {
        spriteWidthDeformationNeeded = 0;
    }
    movement.enterInCollide(infoForMove, dir);
}

void Player::startJump()
{
    if (movement.startJump(infoForMove))
    {
        spriteWidthDeformationNeeded -= 4;
    }
}

void Player::attractTo(sf::Vector2i thisDirection)
{
    infoForMove.currentVerticalVelocity += thisDirection.y;
}

sf::FloatRect Player::getSpriteBox()
{
    return sprite.getGlobalBounds();
}

Direction Player::getDirection()
{
    return currentDir;
}

Direction Player::getVerticalDirection()
{
    if (infoForMove.currentVerticalVelocity < 0)
    {
        return Direction::UP;
    }
    else if (infoForMove.currentVerticalVelocity > 0)
    {
        return Direction::DOWN;
    }
    else
    {
        return Direction::NONE;
    }
}

void Player::setMoveTo(Direction dir)
{
    currentDir = dir;
}

void Player::setMovementForVersion()
{
    movement.setFuncsForGameVersion(Global::versionOfGame);
}

void Player::setVisorForSprite()
{
    spriteVisor.setSize(sf::Vector2f(sprite.getSize().x / 2, 10));

    if (lastDir == Direction::RIGHT)
    {
        spriteVisor.setPosition(sprite.getPosition().x + (sprite.getSize().x / 2), sprite.getPosition().y + 10);
    }
    else if (lastDir == Direction::LEFT)
    {
        spriteVisor.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10);
    }
}
