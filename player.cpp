#include "player.hpp"
#include "global.hpp"
#include "utilities.hpp"

Player::Player() : CharacterImpl{5, 20}
{
    setCanJump(true);
    mSpriteSizeDeformation = {0, 0};
    mBaseSpriteSize = {40, 80};
    mSprite.setFillColor(sf::Color::Blue);
    mSpriteVisor.setFillColor(sf::Color{0, 0, 150});
}

void Player::applyHorizontalMove()
{
    auto oldXPosition = position().x;

    if (mMovement.applyBaseCharacterMove(*this))
    {
        if (mCurrentFrame % 3 == 0 && Global::randomPercentage(Global::fast_random) >= 33 && !(isInJump()) &&
            verticalVelocity() < (GRAVITY * 2))
        {
            if (movingDirection() == Direction::RIGHT)
            {
                mParticleMotor.addParticle(sf::Vector2f(position().x + 5, position().y + mBaseSpriteSize.y), -speed());
            }
            else if (movingDirection() == Direction::LEFT)
            {
                mParticleMotor.addParticle(
                    sf::Vector2f(position().x + mBaseSpriteSize.x - 5, position().y + mBaseSpriteSize.y), speed());
            }
        }

        if (movingDirection() != Direction::NONE)
        {
            mLastDirection = movingDirection();
        }
    }

    mMovement.applySecondaryHorizontalMove(*this);

    if (position().x != oldXPosition)
    {
        setMovedHorizontalDirection((position().x - oldXPosition) > 0 ? Direction::RIGHT : Direction::LEFT);
    }
    else
    {
        setMovedHorizontalDirection(Direction::NONE);
    }
}

void Player::applyVerticalMove()
{
    auto oldYPosition = position().y;

    mMovement.applyVerticalMove(*this);

    if (position().y != oldYPosition)
    {
        setMovedVerticalDirection((position().y - oldYPosition) > 0 ? Direction::DOWN : Direction::UP);
    }
    else
    {
        setMovedVerticalDirection(Direction::NONE);
    }
}

void Player::startJump(bool pSpaceWasPressedLastFrame)
{
    if (mMovement.startJump(*this, pSpaceWasPressedLastFrame))
    {
        mSpriteWidthDeformationNeeded -= 4;
    }
}

void Player::applyGravity(int pGravityStrength)
{
    setVerticalVelocity(verticalVelocity() + pGravityStrength);
}

void Player::setMovementForVersion(const VersionNumber& pVersionOfGame)
{
    mMovement.setFuncsForGameVersion(pVersionOfGame);
}

void Player::updateImpl()
{
    mCurrentFrame = ((mCurrentFrame + 1) % 64);
    setMovingDirection(Direction::NONE);

    if (mCurrentFrame % 2 == 0)
    {
        applySpriteDeformation();
    }

    updateSpriteShape();
    mParticleMotor.update();
}

void Player::drawImpl(sf::RenderWindow& pWindow) const
{
    mParticleMotor.draw(pWindow);
    pWindow.draw(mSprite);
    pWindow.draw(mSpriteVisor);
}

void Player::updateSpriteShape()
{
    if (mSpriteSizeDeformation.y < 0)
    {
        mSprite.setPosition(position().x - (mSpriteSizeDeformation.x / 2), position().y - mSpriteSizeDeformation.y);
    }
    else
    {
        mSprite.setPosition(position().x - (mSpriteSizeDeformation.x / 2), position().y);
    }
    mSprite.setSize(
        sf::Vector2f(mBaseSpriteSize.x + mSpriteSizeDeformation.x, mBaseSpriteSize.y + mSpriteSizeDeformation.y));
    setVisorForSprite();
}

void Player::applySpriteDeformation()
{
    if (mSpriteWidthDeformationNeeded != 0)
    {
        if (mSpriteWidthDeformationNeeded < 0)
        {
            if (!moveSpriteWidthDeformation(-2))
            {
                mSpriteWidthDeformationNeeded = 0;
            }
            else
            {
                ++mSpriteWidthDeformationNeeded;
            }
        }
        else
        {
            if (!moveSpriteWidthDeformation(2))
            {
                mSpriteWidthDeformationNeeded = 0;
            }
            else
            {
                --mSpriteWidthDeformationNeeded;
            }
        }
    }
    else
    {
        if (mSpriteSizeDeformation.x != 0)
        {
            if (mSpriteSizeDeformation.x < 0)
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

bool Player::moveSpriteWidthDeformation(int pAmount)
{
    auto hasMovedFully = true;

    mSpriteSizeDeformation.x += pAmount;
    if (mSpriteSizeDeformation.x > 10)
    {
        mSpriteSizeDeformation.x = 10;
        hasMovedFully = false;
    }
    else if (mSpriteSizeDeformation.x < -10)
    {
        mSpriteSizeDeformation.x = -10;
        hasMovedFully = false;
    }
    mSpriteSizeDeformation.y -= pAmount;
    if (mSpriteSizeDeformation.y > 10)
    {
        mSpriteSizeDeformation.y = 10;
        hasMovedFully = false;
    }
    else if (mSpriteSizeDeformation.y < -10)
    {
        mSpriteSizeDeformation.y = -10;
        hasMovedFully = false;
    }
    return hasMovedFully;
}

void Player::hasEnterInCollideImpl(Direction pDirection)
{
    if (pDirection == Direction::DOWN)
    {
        if (verticalVelocity() > 64)
        {
            mSpriteWidthDeformationNeeded += 5;
        }
        else if (verticalVelocity() > 32)
        {
            mSpriteWidthDeformationNeeded += 4;
        }
        else if (verticalVelocity() > 16)
        {
            mSpriteWidthDeformationNeeded += 3;
        }
        else if (verticalVelocity() > 8)
        {
            mSpriteWidthDeformationNeeded += 2;
        }
        else if (verticalVelocity() > 4)
        {
            mSpriteWidthDeformationNeeded += 1;
        }
    }
    else if (pDirection == Direction::UP)
    {
        mSpriteWidthDeformationNeeded = 0;
    }
    mMovement.applyCollide(*this, pDirection);
}

sf::FloatRect Player::spriteBoxImpl() const
{
    return mSprite.getGlobalBounds();
}

sf::IntRect Player::collideBoxImpl() const
{
    return sf::IntRect{position().x, position().y, mBaseSpriteSize.x, mBaseSpriteSize.y};
}

void Player::setVisorForSprite()
{
    mSpriteVisor.setSize({mSprite.getSize().x / 2.f, 10.f});

    if (mLastDirection == Direction::RIGHT)
    {
        mSpriteVisor.setPosition(mSprite.getPosition().x + (mSprite.getSize().x / 2), mSprite.getPosition().y + 10);
    }
    else if (mLastDirection == Direction::LEFT)
    {
        mSpriteVisor.setPosition(mSprite.getPosition().x, mSprite.getPosition().y + 10);
    }
}
