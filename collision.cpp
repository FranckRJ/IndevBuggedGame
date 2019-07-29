#include "collision.hpp"

void Collision::setFuncsForGameVersion(VersionNumber gameVersion)
{
    // TODO
}

bool Collision::hasCollided(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox)
{
    return (toThisCollideBox.left < (collideBox.left + collideBox.width) &&
            (toThisCollideBox.left + toThisCollideBox.width) > collideBox.left &&
            toThisCollideBox.top < (collideBox.top + collideBox.height) &&
            (toThisCollideBox.top + toThisCollideBox.height) > collideBox.top);
}

sf::Vector2i Collision::getNewPosAfterCollide(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox,
                                              Direction dirOfMovement)
{
    switch (dirOfMovement)
    {
        case Direction::LEFT:
        {
            return sf::Vector2i(toThisCollideBox.left + toThisCollideBox.width, collideBox.top);
        }
        case Direction::UP:
        {
            return sf::Vector2i(collideBox.left, toThisCollideBox.top + toThisCollideBox.height);
        }
        case Direction::RIGHT:
        {
            return sf::Vector2i(toThisCollideBox.left - collideBox.width, collideBox.top);
        }
        case Direction::DOWN:
        {
            return sf::Vector2i(collideBox.left, toThisCollideBox.top - collideBox.height);
        }
        default:
        {
            return sf::Vector2i(collideBox.left, collideBox.top);
        }
    }
}
