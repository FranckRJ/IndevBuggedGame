#include "collision.hpp"
#include "block.hpp"

void Collision::setFuncsForGameVersion(VersionNumber gameVersion)
{
    // TODO
    (void)gameVersion;
}

bool Collision::isCollidingBlock(Character& character, const Block& block, Direction movementDir)
{
    sf::IntRect characterCollideBox = character.collideBox();
    sf::IntRect blockCollideBox = block.collideBox();

    (void)movementDir;
    return (blockCollideBox.left < (characterCollideBox.left + characterCollideBox.width) &&
            (blockCollideBox.left + blockCollideBox.width) > characterCollideBox.left &&
            blockCollideBox.top < (characterCollideBox.top + characterCollideBox.height) &&
            (blockCollideBox.top + blockCollideBox.height) > characterCollideBox.top);
}

void Collision::replaceCharacterNearBlock(Character& character, const Block& block, Direction movementDir)
{
    sf::IntRect characterCollideBox = character.collideBox();
    sf::IntRect blockCollideBox = block.collideBox();

    switch (movementDir)
    {
        case Direction::LEFT:
        {
            character.setPosition({blockCollideBox.left + blockCollideBox.width, characterCollideBox.top});
            break;
        }
        case Direction::UP:
        {
            character.setPosition({characterCollideBox.left, blockCollideBox.top + blockCollideBox.height});
            break;
        }
        case Direction::RIGHT:
        {
            character.setPosition({blockCollideBox.left - characterCollideBox.width, characterCollideBox.top});
            break;
        }
        case Direction::DOWN:
        {
            character.setPosition({characterCollideBox.left, blockCollideBox.top - characterCollideBox.height});
            break;
        }
        default:
        {
            character.setPosition({characterCollideBox.left, characterCollideBox.top});
            break;
        }
    }
}
