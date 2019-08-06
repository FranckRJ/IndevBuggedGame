#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "versionNumber.hpp"

class Block;

class Collision
{
public:
    void setFuncsForGameVersion(const VersionNumber& pGameVersion);
    bool isCollidingBlock(Character& pCharacter, const Block& pBlock, Direction pMovementDir);
    void replaceCharacterNearBlock(Character& pCharacter, const Block& pBlock, Direction pMovementDir);
};

#endif
