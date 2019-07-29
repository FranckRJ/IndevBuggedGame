#include "player.hpp"
#include "global.hpp"
#include "utilities.hpp"

Player::Player()
{
    speed = 5;
    jumpPower = -20;
    currentVerticalVelocity = 0;
    canJump = true;
    canMoveIntentionally = true;
    isInJump = false;
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
    currentDirection = Direction::NONE;

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

void Player::applyHorizontalMove()
{
    int oldXPosition = position.x;

    if (movement.applyBaseCharacterMove(*this))
    {
        if (currentFrame % 8 == 0 && !(isInJump) && currentVerticalVelocity < (GRAVITY * 2))
        {
            if (currentDirection == Direction::RIGHT)
            {
                particleMotor.addParticle(sf::Vector2f(position.x, position.y + sizeOfCollideBox.y), -speed);
            }
            else if (currentDirection == Direction::LEFT)
            {
                particleMotor.addParticle(
                    sf::Vector2f(position.x + sizeOfCollideBox.x, position.y + sizeOfCollideBox.y), speed);
            }
        }

        if (currentDirection != Direction::NONE)
        {
            lastDirection = currentDirection;
        }
    }

    movement.applySecondaryHorizontalMove(*this);

    if (position.x != oldXPosition)
    {
        movedHorizontalDirection = ((position.x - oldXPosition) > 0 ? Direction::RIGHT : Direction::LEFT);
    }
    else
    {
        movedHorizontalDirection = Direction::NONE;
    }
}

void Player::applyVerticalMove()
{
    int oldYPosition = position.y;

    movement.applyVerticalMove(*this);

    if (position.y != oldYPosition)
    {
        movedVerticalDirection = ((position.y - oldYPosition) > 0 ? Direction::DOWN : Direction::UP);
    }
    else
    {
        movedVerticalDirection = Direction::NONE;
    }
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
        if (currentVerticalVelocity > 64)
        {
            spriteWidthDeformationNeeded += 5;
        }
        else if (currentVerticalVelocity > 32)
        {
            spriteWidthDeformationNeeded += 4;
        }
        else if (currentVerticalVelocity > 16)
        {
            spriteWidthDeformationNeeded += 3;
        }
        else if (currentVerticalVelocity > 8)
        {
            spriteWidthDeformationNeeded += 2;
        }
        else if (currentVerticalVelocity > 4)
        {
            spriteWidthDeformationNeeded += 1;
        }
    }
    else if (dir == Direction::UP)
    {
        spriteWidthDeformationNeeded = 0;
    }
    movement.applyCollide(*this, dir);
}

void Player::startJump(bool spaceWasPressedLastFrame)
{
    if (movement.startJump(*this, spaceWasPressedLastFrame))
    {
        spriteWidthDeformationNeeded -= 4;
    }
}

void Player::applyGravity(int gravityStrength)
{
    currentVerticalVelocity += gravityStrength;
}

sf::FloatRect Player::getSpriteBox()
{
    return sprite.getGlobalBounds();
}

void Player::setMovementForVersion()
{
    movement.setFuncsForGameVersion(Global::versionOfGame);
}

void Player::setVisorForSprite()
{
    spriteVisor.setSize(sf::Vector2f(sprite.getSize().x / 2, 10));

    if (lastDirection == Direction::RIGHT)
    {
        spriteVisor.setPosition(sprite.getPosition().x + (sprite.getSize().x / 2), sprite.getPosition().y + 10);
    }
    else if (lastDirection == Direction::LEFT)
    {
        spriteVisor.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10);
    }
}
