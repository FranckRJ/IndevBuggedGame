#include "collision.hpp"

bool collisionClass::isColliAll(typeColli typeOfColli, sf::FloatRect collideBox, sf::FloatRect toThisCollideBox)
{
    switch(typeOfColli)
    {
        case ALL_NORMAL:
        {
            return normalAllColli(collideBox, toThisCollideBox);
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

sf::Vector2i collisionClass::getNewPosColliAll(typeColli typeOfColli, sf::FloatRect collideBox, sf::FloatRect toThisCollideBox, direction dir)
{
    switch(typeOfColli)
    {
        case ALL_NORMAL:
        {
            return getNewPosNormalAllColli(collideBox, toThisCollideBox, dir);
            break;
        }
        default:
        {
            return sf::Vector2i(collideBox.left, collideBox.top);
            break;
        }
    }
}
