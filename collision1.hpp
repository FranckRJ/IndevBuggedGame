#ifndef COLLISION1_HPP
#define COLLISION1_HPP

#include "collision.hpp"

class collision1Class : public collisionClass
{
public:
    bool normalAllColli(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox);
    sf::Vector2i getNewPosNormalAllColli(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox, direction dir);
};

#endif
