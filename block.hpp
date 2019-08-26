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
    sf::RectangleShape sprite{};
    BlockId id{};
};

struct BlockProperties
{
    bool isFinishTrigger = false;
    bool isSolid = false;
    bool isTriggeredContinuously = true;
    bool isDeadlyToPlayer = false;
    bool isInForeground = false;
    std::map<Character::Status, bool> temporaryEffects = {};
    sf::Vector2i addVelocityToCharacter = {0, 0};
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
    Block(const BlockProperties& pProperties, const BlockSprite& pSpriteInfos, BlockId pId);

    void update();
    void draw(sf::RenderWindow& pWindow);

    sf::IntRect collideBox() const;
    const BlockProperties blockInfos() const;
    bool wasInCollideLastFrame() const;

    void setPosition(sf::Vector2i pPosition);
    void setCollisionForVersion(const VersionNumber& pVersionOfGame);

    bool applyCollision(Character& pCharacter, Direction pMovementDir, bool pOnlyPositionCheck);

private:
    bool mWasInCollideLastFrame = false;
    bool mHasCheckedCollideLastFrame = false;
    sf::RectangleShape mSprite;
    sf::Vector2i mPosition = {0, 0};
    Collision mCollision;
    const BlockProperties& mProperties;
    const BlockSprite& mSpriteInfos;
    const BlockId mId;
};

#endif
