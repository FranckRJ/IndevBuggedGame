#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "versionNumber.hpp"

class Block;

class Collision
{
public:
    void setFuncsForGameVersion(VersionNumber gameVersion);
    bool isCollidingBlock(Character& character, const Block& block, Direction movementDir);
    void replaceCharacterNearBlock(Character& character, const Block& block, Direction movementDir);
};

#endif
