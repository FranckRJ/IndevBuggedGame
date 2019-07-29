#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

#include "blockId.hpp"
#include "collision.hpp"
#include "direction.hpp"
#include "global.hpp"

class Character;

struct BasicBlock
{
    sf::RectangleShape sprite;
    BlockId id;
};

struct BlockProperties
{
    bool isFinishTrigger = false;
    bool isSolid = false;
    bool isTriggeredContinuously = true;
    bool isDeadlyToPlayer = false;
    bool isInForeground = false;
    bool doStopPlayerFromMoving = false;
    sf::Vector2i affectCharacterMove = sf::Vector2i(0, 0);
};

struct BlockSprite
{
    sf::Vector2i margin = sf::Vector2i(0, 0);
    sf::Vector2i size = sf::Vector2i(SIZE_BLOCK, SIZE_BLOCK);
    sf::Color color = sf::Color::Black;
};

struct BlockInfos
{
    BlockProperties properties;
    BlockSprite spriteInfos;
};

class Block
{
public:
    Block(const BlockProperties& newProperties, const BlockSprite& newSpriteInfos, BlockId newId);
    void update();
    void draw(sf::RenderWindow& window);
    bool applyCollision(Character& character, Direction movementDir, bool onlyPositionCheck);
    sf::IntRect getCollideBox() const;
    const BlockProperties getBlockInfo();
    bool getWasInCollideLastFrame();
    void setPosition(sf::Vector2i newPosition);
    void setPosition(int newX, int newY);
    void setCollisionForVersion();

private:
    bool wasInCollideLastFrame = false;
    bool hasCheckedCollideLastFrame = false;
    sf::RectangleShape sprite;
    sf::Vector2i position;
    Collision collision;
    const BlockProperties& properties;
    const BlockSprite& spriteInfos;
    const BlockId id;
};

#endif
