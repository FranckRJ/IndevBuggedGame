#include "collision1.hpp"

bool collision1Class::normalAllColli(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox)
{
    if(toThisCollideBox.left < (collideBox.left + collideBox.width) && (toThisCollideBox.left + toThisCollideBox.width) > collideBox.left && toThisCollideBox.top < (collideBox.top + collideBox.height) && (toThisCollideBox.top + toThisCollideBox.height) > collideBox.top)
    {
        return true;
    }
    else
    {
        return false;
    }
}


sf::Vector2i collision1Class::getNewPosNormalAllColli(sf::FloatRect collideBox, sf::FloatRect toThisCollideBox, direction dir)
{
    switch(dir)
    {
        case LEFT:
        {
            return sf::Vector2i(toThisCollideBox.left + toThisCollideBox.width, collideBox.top);
            break;
        }
        case UP:
        {
            return sf::Vector2i(collideBox.left, toThisCollideBox.top + toThisCollideBox.height);
            break;
        }
        case RIGHT:
        {
            return sf::Vector2i(toThisCollideBox.left - collideBox.width, collideBox.top);
            break;
        }
        case DOWN:
        {
            return sf::Vector2i(collideBox.left, toThisCollideBox.top - collideBox.height);
            break;
        }
        default:
        {
            return sf::Vector2i(collideBox.left, collideBox.top);
            break;
        }
    }
}
