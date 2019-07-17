#include "movementX.hpp"

sf::Vector2i movementXClass::moveCharacterTo(moveInfo& infoForMove, direction dir, sf::Vector2i position)
{
    if(dir == RIGHT)
    {
        position.x += infoForMove.speed;
    }
    else if(dir == LEFT)
    {
        position.x -= infoForMove.speed;
    }

    return position;
}

sf::Vector2i movementXClass::applyGravity(moveInfo& infoForMove, sf::Vector2i position)
{
    position.y += infoForMove.currentVerticalVelocity;
    return position;
}

void movementXClass::enterInCollide(moveInfo& infoForMove, direction dir)
{
    if(dir == UP || dir == DOWN)
    {
        infoForMove.currentVerticalVelocity = 0;

        if(dir == DOWN)
        {
            infoForMove.canJump = true;
            infoForMove.isInJump = false;
        }
    }
}

bool movementXClass::startJump(moveInfo& infoForMove)
{
    if(infoForMove.canJump)
    {
        infoForMove.currentVerticalVelocity = infoForMove.jumpPower;
        infoForMove.canJump = false;
        infoForMove.isInJump = true;
        return true;
    }

    return false;
}
