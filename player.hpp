#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "character.hpp"
#include "movement.hpp"
#include "particleMotor.hpp"

class Player : public Character
{
public:
    Player();
    void update();
    void draw(sf::RenderWindow& window);
    void updateSpriteShape();
    bool applyMove();
    bool applyVerticalMove();
    void applySpriteDeformation();
    bool moveSpriteWidthDeformation(int amount);
    void hasEnterInCollide(Direction dir);
    void startJump();
    void attractTo(sf::Vector2i thisDirection);
    sf::FloatRect getSpriteBox();
    Direction getDirection();
    Direction getVerticalDirection();
    void setMoveTo(Direction dir);
    void setMovementForVersion();
    void setVisorForSprite();

private:
    sf::RectangleShape sprite;
    sf::RectangleShape spriteVisor;
    sf::Vector2i baseSpriteSize;
    sf::Vector2i spriteSizeDeformation;
    int currentFrame = 0;
    int spriteWidthDeformationNeeded = 0;
    ParticleMotor particleMotor;
    MovementClass movement;
    Direction currentDir = Direction::NONE;
    Direction lastDir = Direction::RIGHT;
};

#endif
