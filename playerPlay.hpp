#ifndef PLAYERPLAY_HPP
#define PLAYERPLAY_HPP

#include <memory>

#include "character.hpp"
#include "movement.hpp"
#include "particleMotor.hpp"

class playerPlayClass : public characterClass
{
public:
    playerPlayClass();
    void update();
    void draw(sf::RenderWindow& window);
    void updateSpriteShape();
    bool applyMove();
    bool applyVerticalMove();
    void applySpriteDeformation();
    bool moveSpriteWidthDeformation(int amount);
    void hasEnterInCollide(direction dir);
    void startJump();
    void attractTo(sf::Vector2i thisDirection);
    sf::FloatRect getSpriteBox();
    direction getDirection();
    direction getVerticalDirection();
    void setMoveTo(direction dir);
    void setMovementForVersion();
    void setVisorForSprite();

private:
    sf::RectangleShape sprite;
    sf::RectangleShape spriteVisor;
    sf::Vector2i baseSpriteSize;
    sf::Vector2i spriteSizeDeformation;
    int currentFrame = 0;
    int spriteWidthDeformationNeeded = 0;
    particleMotorClass particleMotor;
    movementClass movement;
    direction currentDir = direction::NONE;
    direction lastDir = direction::RIGHT;
};

#endif
