#include "movement.hpp"

namespace
{
    sf::Vector2i moveCharacterToV1_0(MoveInfos& infoForMove, Direction dir, sf::Vector2i position)
    {
        if (dir == Direction::RIGHT)
        {
            position.x += infoForMove.speed;
        }

        return position;
    }

    sf::Vector2i moveCharacterToV1_1(MoveInfos& infoForMove, Direction dir, sf::Vector2i position)
    {
        if (dir == Direction::RIGHT)
        {
            position.x += infoForMove.speed;
        }
        else if (dir == Direction::LEFT)
        {
            position.x -= infoForMove.speed;
        }

        return position;
    }

    sf::Vector2i applyGravityV1_0(MoveInfos& infoForMove, sf::Vector2i position)
    {
        position.y += static_cast<int>(infoForMove.currentVerticalVelocity);
        return position;
    }

    void enterInCollideV1_0(MoveInfos& infoForMove, Direction dir)
    {
        if (dir == Direction::UP || dir == Direction::DOWN)
        {
            if (infoForMove.currentVerticalVelocity > 100)
            {
                infoForMove.currentVerticalVelocity = 99;
            }
            else
            {
                infoForMove.currentVerticalVelocity = 0;
            }

            if (dir == Direction::DOWN)
            {
                infoForMove.isInJump = false;
            }
        }
        if (dir != Direction::NONE)
        {
            infoForMove.canJump = true;
        }
    }

    void enterInCollideV1_4(MoveInfos& infoForMove, Direction dir)
    {
        if (dir == Direction::UP || dir == Direction::DOWN)
        {
            infoForMove.currentVerticalVelocity = 0;

            if (dir == Direction::DOWN)
            {
                infoForMove.isInJump = false;
            }

            infoForMove.canJump = true;
        }
    }

    void enterInCollideV1_5(MoveInfos& infoForMove, Direction dir)
    {
        if (dir == Direction::UP || dir == Direction::DOWN)
        {
            infoForMove.currentVerticalVelocity = 0;

            if (dir == Direction::DOWN)
            {
                infoForMove.canJump = true;
                infoForMove.isInJump = false;
            }
        }
    }

    bool startJumpV1_0(MoveInfos& infoForMove)
    {
        (void)infoForMove;
        return false;
    }

    bool startJumpV1_2(MoveInfos& infoForMove)
    {
        infoForMove.currentVerticalVelocity = infoForMove.jumpPower;
        infoForMove.canJump = false;
        infoForMove.isInJump = true;
        return true;
    }

    bool startJumpV1_3(MoveInfos& infoForMove)
    {
        if (infoForMove.canJump)
        {
            infoForMove.currentVerticalVelocity = infoForMove.jumpPower;
            infoForMove.canJump = false;
            infoForMove.isInJump = true;
            return true;
        }

        return false;
    }
} // namespace

void MovementClass::setFuncsForGameVersion(const VersionNumber& gameVersion)
{
    /* TODO: changer la maniere dont est gere gameVersion. */
    resetAllInternalFuncs();
    moveCharacterToFunc = moveCharacterToV1_0;
    applyGravityFunc = applyGravityV1_0;
    enterInCollideFunc = enterInCollideV1_0;
    startJumpFunc = startJumpV1_0;

    if (gameVersion >= "1.1"_vn)
    {
        moveCharacterToFunc = moveCharacterToV1_1;
    }
    if (gameVersion >= "1.2"_vn)
    {
        startJumpFunc = startJumpV1_2;
    }
    if (gameVersion >= "1.3"_vn)
    {
        startJumpFunc = startJumpV1_3;
    }
    if (gameVersion >= "1.4"_vn)
    {
        enterInCollideFunc = enterInCollideV1_4;
    }
    if (gameVersion >= "1.5"_vn)
    {
        enterInCollideFunc = enterInCollideV1_5;
    }
}

sf::Vector2i MovementClass::moveCharacterTo(MoveInfos& infoForMove, Direction dir, sf::Vector2i position)
{
    if (moveCharacterToFunc)
    {
        return moveCharacterToFunc(infoForMove, dir, position);
    }
    else
    {
        return position;
    }
}

sf::Vector2i MovementClass::applyGravity(MoveInfos& infoForMove, sf::Vector2i position)
{

    if (applyGravityFunc)
    {
        return applyGravityFunc(infoForMove, position);
    }
    else
    {
        return position;
    }
}

void MovementClass::enterInCollide(MoveInfos& infoForMove, Direction dir)
{
    if (enterInCollideFunc)
    {
        return enterInCollideFunc(infoForMove, dir);
    }
}

bool MovementClass::startJump(MoveInfos& infoForMove)
{
    if (startJumpFunc)
    {
        return startJumpFunc(infoForMove);
    }
    else
    {
        return false;
    }
}

void MovementClass::resetAllInternalFuncs()
{
    moveCharacterToFunc = nullptr;
    applyGravityFunc = nullptr;
    enterInCollideFunc = nullptr;
    startJumpFunc = nullptr;
}
