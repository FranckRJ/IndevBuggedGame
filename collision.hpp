#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "versionNumber.hpp"

class collisionClass
{
public:
    void setFuncsForGameVersion(versionNumberClass gameVersion);
    bool hasCollided(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox);
    sf::Vector2i getNewPosAfterCollide(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox,
                                       direction dirOfMovement);
};

#endif
