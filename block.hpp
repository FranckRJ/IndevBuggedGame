#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "character.hpp"
#include "collision.hpp"
#include "global.hpp"

struct basicBlock
{
    sf::RectangleShape sprite;
    std::string name;
};

struct blockProperties
{
    bool isFinishTrigger = false;
    bool isSolid = false;
    bool isTriggeredContinuously = true;
    bool isDeadlyToPlayer = false;
    bool isInForeground = false;
};

struct blockSprite
{
    sf::Vector2i margin = sf::Vector2i(0, 0);
    sf::Vector2i size = sf::Vector2i(SIZE_BLOCK, SIZE_BLOCK);
    sf::Color color = sf::Color::Black;
};

class blockClass
{
public:
    blockClass(const blockProperties& newProperties, const blockSprite& newSpriteInfos);
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
    bool wasInCollideLastFrame = false;
    bool hasCheckedCollideLastFrame = false;
    sf::RectangleShape sprite;
    sf::Vector2i position;
    collisionClass collision;
    const blockProperties& properties;
    const blockSprite& spriteInfos;
};

#endif
