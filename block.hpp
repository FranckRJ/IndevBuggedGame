#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "character.hpp"
#include "collision.hpp"

struct basicBlock
{
    sf::RectangleShape sprite;
    std::string name;
};

struct blockProperties
{
    bool isFinishTrigger;
    bool isSolid;
    bool isTriggeredContinuously;
    bool isDeadlyToPlayer;
    bool isInForeground;
};

struct blockSprite
{
    sf::Vector2i margin;
    sf::Vector2i size;
    sf::Color color;
};

class blockClass
{
public:
    blockClass();
    blockClass(blockProperties newProperties, blockSprite newSpriteInfos);
    void update();
    void draw(sf::RenderWindow& window);
    bool isCollideWith(sf::FloatRect collideBox);
    sf::Vector2i getNewPosOf(sf::FloatRect collideBox, direction dir);
    const blockProperties getBlockInfo();
    bool getWasInCollideLastFrame();
    void setPosition(sf::Vector2i newPosition);
    void setPosition(int newX, int newY);
    void setCollisionForVersion();

private:
    bool wasInCollideLastFrame;
    bool hasCheckedCollideLastFrame;
    sf::RectangleShape sprite;
    sf::Vector2i position;
    collisionClass collision;
    blockProperties properties;
    blockSprite spriteInfos;
};

#endif
