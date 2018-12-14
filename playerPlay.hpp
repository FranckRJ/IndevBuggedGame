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
    bool applyMove();
    bool applyVerticalMove();
    void applySpriteDeformation();
    void moveSpriteDeformation(int amount);
    void hasEnterInCollide(direction dir);
    void startJump();
    void attractTo(sf::Vector2i thisDirection);
    bool getIsDead();
    sf::FloatRect getSpriteBox();
    sf::FloatRect getCollideBox();
    sf::Vector2i getPosition();
    direction getDirection();
    direction getVerticalDirection();
    void setIsDead(bool newVal);
    void setMoveTo(direction dir);
    void setPosition(sf::Vector2i newPosition);
    void setPosition(int newX, int newY);
    void setMovementForVersion();
    void setVisorForSprite();
private:
    sf::RectangleShape sprite;
    sf::RectangleShape spriteVisor;
    sf::Vector2f spriteDeformation;
    int currentFrame;
    int spriteDeformationNeeded;
    particleMotorClass particleMotor;
    std::unique_ptr<movementClass> movement;
    direction currentDir;
    direction lastDir;
};

#endif