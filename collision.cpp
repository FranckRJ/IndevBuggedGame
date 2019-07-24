#include "collision.hpp"

void collisionClass::setFuncsForGameVersion(versionNumberClass gameVersion)
{
    // TODO
}

bool collisionClass::hasCollided(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox)
{
    return (toThisCollideBox.left < (collideBox.left + collideBox.width) &&
            (toThisCollideBox.left + toThisCollideBox.width) > collideBox.left &&
            toThisCollideBox.top < (collideBox.top + collideBox.height) &&
            (toThisCollideBox.top + toThisCollideBox.height) > collideBox.top);
}

sf::Vector2i collisionClass::getNewPosAfterCollide(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox,
                                                   direction dirOfMovement)
{
    switch (dirOfMovement)
    {
        case LEFT:
        {
            return sf::Vector2i(toThisCollideBox.left + toThisCollideBox.width, collideBox.top);
        }
        case UP:
        {
            return sf::Vector2i(collideBox.left, toThisCollideBox.top + toThisCollideBox.height);
        }
        case RIGHT:
        {
            return sf::Vector2i(toThisCollideBox.left - collideBox.width, collideBox.top);
        }
        case DOWN:
        {
            return sf::Vector2i(collideBox.left, toThisCollideBox.top - collideBox.height);
        }
        default:
        {
            return sf::Vector2i(collideBox.left, collideBox.top);
        }
    }
}
