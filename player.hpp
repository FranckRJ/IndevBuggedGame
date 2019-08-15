#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "character.hpp"
#include "movement.hpp"
#include "particleMotor.hpp"

class Player : public CharacterImpl
{
public:
    Player();
    void applyHorizontalMove();
    void applyVerticalMove();
    void startJump(bool spaceWasPressedLastFrame);
    void applyGravity(int gravityStrength);
    void setMovementForVersion(const VersionNumber &pVersionOfGame);

private:
    void updateImpl() override;
    void drawImpl(sf::RenderWindow& window) override;
    void updateSpriteShape();
    void applySpriteDeformation();
    bool moveSpriteWidthDeformation(int amount);
    void hasEnterInCollideImpl(Direction pDirection) override;
    sf::FloatRect spriteBoxImpl() const override;
    sf::IntRect collideBoxImpl() const override;
    void setVisorForSprite();

private:
    sf::RectangleShape mSprite;
    sf::RectangleShape mSpriteVisor;
    sf::Vector2i mBaseSpriteSize = {0, 0};
    sf::Vector2i mSpriteSizeDeformation;
    int mCurrentFrame = 0;
    int mSpriteWidthDeformationNeeded = 0;
    ParticleMotor mParticleMotor;
    MovementClass mMovement;
    Direction mLastDirection = Direction::RIGHT;
};

#endif
