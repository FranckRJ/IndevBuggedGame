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

struct blockInfo
{
    bool isFinishBlock;
    bool isSolidBlock;
    bool isOnlyOneBlock;
    bool isKillPlayerBlock;
    bool isForegroundBlock;
};

struct blockType
{
    sf::Vector2i spaceOfBlock;
    sf::Vector2i sizeOfBlock;
    sf::Color colorOfBlock;
};

class blockClass
{
public:
    blockClass();
    blockClass(blockInfo newInfoForBlock, blockType newTypeOfBlock);
    void update();
    void draw(sf::RenderWindow& window);
    bool isCollideWith(sf::FloatRect collideBox);
    sf::Vector2i getNewPosOf(sf::FloatRect collideBox, direction dir);
    const blockInfo getBlockInfo();
    bool getOldCollide();
    void setPosition(sf::Vector2i newPosition);
    void setPosition(int newX, int newY);
    void setCollisionForVersion();

private:
    bool oldCollide;
    bool collideCheckLastFrame;
    sf::RectangleShape sprite;
    sf::Vector2i position;
    collisionClass collision;
    blockInfo infoForBlock;
    blockType typeOfBlock;
};

#endif
