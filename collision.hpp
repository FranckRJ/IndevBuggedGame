#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/Graphics.hpp>

#include "character.hpp"

enum dirColli {COLLI_LEFT, COLLI_TOP, COLLI_RIGHT, COLLI_BOTTOM, COLLI_ALL};
enum typeColli {ALL_NORMAL};

class collisionClass
{
public:
    virtual bool isColliAll(typeColli typeOfColli, sf::FloatRect collideBox, sf::FloatRect toThisCollideBox);
    virtual sf::Vector2i getNewPosColliAll(typeColli typeOfColli, sf::FloatRect collideBox, sf::FloatRect toThisCollideBox, direction dir);
    virtual bool normalAllColli(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox) = 0;
    virtual sf::Vector2i getNewPosNormalAllColli(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox, direction dir) = 0;
};

#endif
