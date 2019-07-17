#include "movement1.hpp"
#include "global.hpp"

sf::Vector2i movement1Class::moveCharacterTo(moveInfo& infoForMove, direction dir, sf::Vector2i position)
{
    if(dir == RIGHT)
    {
        position.x += infoForMove.speed;
    }
    else if(dir == LEFT && global::versionOfGame > 1.05)
    {
        position.x -= infoForMove.speed;
    }

    return position;
}

sf::Vector2i movement1Class::applyGravity(moveInfo& infoForMove, sf::Vector2i position)
{
    position.y += infoForMove.currentVerticalVelocity;
    return position;
}

void movement1Class::enterInCollide(moveInfo& infoForMove, direction dir)
{
    if(dir == UP || dir == DOWN)
    {
        if(global::versionOfGame < 1.35 && infoForMove.currentVerticalVelocity > 100)
        {
            infoForMove.currentVerticalVelocity = 99;
        }
        else
        {
            infoForMove.currentVerticalVelocity = 0;
        }

        if(dir == DOWN)
        {
            infoForMove.canJump = true;
            infoForMove.isInJump = false;
        }

        if(global::versionOfGame < 1.45)
        {
            infoForMove.canJump = true;
        }
    }
    if(dir != NONE && global::versionOfGame < 1.35)
    {
        infoForMove.canJump = true;
    }
}

bool movement1Class::startJump(moveInfo& infoForMove)
{
    if((global::versionOfGame > 1.25 && infoForMove.canJump) || (global::versionOfGame > 1.15 && global::versionOfGame < 1.25))
    {
        infoForMove.currentVerticalVelocity = infoForMove.jumpPower;
        infoForMove.canJump = false;
        infoForMove.isInJump = true;
        return true;
    }

    return false;
}
