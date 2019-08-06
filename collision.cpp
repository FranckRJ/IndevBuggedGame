#include "collision.hpp"
#include "block.hpp"

void Collision::setFuncsForGameVersion(const VersionNumber& pGameVersion)
{
    // TODO
    (void)pGameVersion;
}

bool Collision::isCollidingBlock(Character& pCharacter, const Block& pBlock, Direction pMovementDir)
{
    auto characterCollideBox = pCharacter.collideBox();
    auto blockCollideBox = pBlock.collideBox();

    (void)pMovementDir;
    return (blockCollideBox.left < (characterCollideBox.left + characterCollideBox.width) &&
            (blockCollideBox.left + blockCollideBox.width) > characterCollideBox.left &&
            blockCollideBox.top < (characterCollideBox.top + characterCollideBox.height) &&
            (blockCollideBox.top + blockCollideBox.height) > characterCollideBox.top);
}

void Collision::replaceCharacterNearBlock(Character& pCharacter, const Block& pBlock, Direction pMovementDir)
{
    auto characterCollideBox = pCharacter.collideBox();
    auto blockCollideBox = pBlock.collideBox();

    switch (pMovementDir)
    {
        case Direction::LEFT:
        {
            pCharacter.setPosition({blockCollideBox.left + blockCollideBox.width, characterCollideBox.top});
            break;
        }
        case Direction::UP:
        {
            pCharacter.setPosition({characterCollideBox.left, blockCollideBox.top + blockCollideBox.height});
            break;
        }
        case Direction::RIGHT:
        {
            pCharacter.setPosition({blockCollideBox.left - characterCollideBox.width, characterCollideBox.top});
            break;
        }
        case Direction::DOWN:
        {
            pCharacter.setPosition({characterCollideBox.left, blockCollideBox.top - characterCollideBox.height});
            break;
        }
        default:
        {
            pCharacter.setPosition({characterCollideBox.left, characterCollideBox.top});
            break;
        }
    }
}
