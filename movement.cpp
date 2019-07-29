#include "movement.hpp"
#include "blockManager.hpp"
#include "utilities.hpp"

namespace
{
    bool applyBaseCharacterMoveV1_0(Character& character)
    {
        if (character.getCanMoveIntentionally() && character.getCurrentDirection() != Direction::NONE)
        {
            if (character.getCurrentDirection() == Direction::RIGHT)
            {
                character.changePosition(character.getSpeed(), 0);
                return true;
            }
        }

        return false;
    }

    bool applyBaseCharacterMoveV1_1(Character& character)
    {
        if (character.getCanMoveIntentionally() && character.getCurrentDirection() != Direction::NONE)
        {
            if (character.getCurrentDirection() == Direction::RIGHT)
            {
                character.changePosition(character.getSpeed(), 0);
                return true;
            }
            else if (character.getCurrentDirection() == Direction::LEFT)
            {
                character.changePosition(-character.getSpeed(), 0);
                return true;
            }
        }

        return false;
    }

    bool applySecondaryHorizontalMoveV1_0(Character& character)
    {
        int changeToXPosition = 0;

        for (const BlockId& id : character.getSetOfBlocksAffectingMove())
        {
            changeToXPosition += BlockManager::getBlockInfos(id).properties.affectCharacterMove.x;
        }

        if (changeToXPosition != 0)
        {
            character.changePosition(changeToXPosition, 0);
            return true;
        }

        return false;
    }

    bool applyVerticalMoveV1_0(Character& character)
    {
        if (!Utilities::doubleIsNear(character.getCurrentVerticalVelocity(), 0.0))
        {
            character.changePosition(0, static_cast<int>(character.getCurrentVerticalVelocity()));
            return true;
        }

        return false;
    }

    void applyCollideV1_0(Character& character, Direction collideDir)
    {
        if (collideDir == Direction::UP || collideDir == Direction::DOWN)
        {
            if (character.getCurrentVerticalVelocity() > 100)
            {
                character.setCurrentVerticalVelocity(99);
            }
            else
            {
                character.setCurrentVerticalVelocity(0);
            }

            if (collideDir == Direction::DOWN)
            {
                character.setIsInJump(false);
            }
        }
        if (collideDir != Direction::NONE)
        {
            character.setCanJump(true);
        }
    }

    void applyCollideV1_4(Character& character, Direction collideDir)
    {
        if (collideDir == Direction::UP || collideDir == Direction::DOWN)
        {
            character.setCurrentVerticalVelocity(0);

            if (collideDir == Direction::DOWN)
            {
                character.setIsInJump(false);
            }

            character.setCanJump(true);
        }
    }

    void applyCollideV1_5(Character& character, Direction collideDir)
    {
        if (collideDir == Direction::UP || collideDir == Direction::DOWN)
        {
            character.setCurrentVerticalVelocity(0);

            if (collideDir == Direction::DOWN)
            {
                character.setCanJump(true);
                character.setIsInJump(false);
            }
        }
    }

    bool startJumpV1_0(Character& character, bool spaceWasPressedLastFrame)
    {
        (void)character;
        (void)spaceWasPressedLastFrame;
        return false;
    }

    bool startJumpV1_2(Character& character, bool spaceWasPressedLastFrame)
    {
        (void)spaceWasPressedLastFrame;

        if (character.getCanJumpIntentionally())
        {
            character.setCurrentVerticalVelocity(character.getJumpPower());
            character.setCanJump(false);
            character.setIsInJump(true);
            return true;
        }

        return false;
    }

    bool startJumpV1_3(Character& character, bool spaceWasPressedLastFrame)
    {
        (void)spaceWasPressedLastFrame;

        if (character.getCanJumpIntentionally() && character.getCanJump())
        {
            character.setCurrentVerticalVelocity(character.getJumpPower());
            character.setCanJump(false);
            character.setIsInJump(true);
            return true;
        }

        return false;
    }

    bool startJumpV1_5(Character& character, bool spaceWasPressedLastFrame)
    {
        if (character.getCanJumpIntentionally())
        {
            if (character.getCanJump())
            {
                character.setCurrentVerticalVelocity(character.getJumpPower());
                character.setCanJump(false);
                character.setIsInJump(true);
                return true;
            }
            else if (!spaceWasPressedLastFrame)
            {
                character.setCurrentVerticalVelocity(0);
            }
        }

        return false;
    }

    bool startJumpV1_6(Character& character, bool spaceWasPressedLastFrame)
    {
        (void)spaceWasPressedLastFrame;

        if (character.getCanJumpIntentionally())
        {
            if (character.getCanJump())
            {
                character.setCurrentVerticalVelocity(character.getJumpPower());
                character.setCanJump(false);
                character.setIsInJump(true);
                return true;
            }
        }

        return false;
    }
} // namespace

void MovementClass::setFuncsForGameVersion(const VersionNumber& gameVersion)
{
    /* TODO: changer la maniere dont est gere gameVersion. */
    resetAllInternalFuncs();
    applyBaseCharacterMoveFunc = applyBaseCharacterMoveV1_0;
    applySecondaryHorizontalMoveFunc = applySecondaryHorizontalMoveV1_0;
    applyVerticalMoveFunc = applyVerticalMoveV1_0;
    applyCollideFunc = applyCollideV1_0;
    startJumpFunc = startJumpV1_0;

    if (gameVersion >= "1.1"_vn)
    {
        applyBaseCharacterMoveFunc = applyBaseCharacterMoveV1_1;
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
        applyCollideFunc = applyCollideV1_4;
    }
    if (gameVersion >= "1.5"_vn)
    {
        applyCollideFunc = applyCollideV1_5;
        startJumpFunc = startJumpV1_5;
    }
    if (gameVersion >= "1.6"_vn)
    {
        startJumpFunc = startJumpV1_6;
    }
}

bool MovementClass::applyBaseCharacterMove(Character& character)
{
    if (applyBaseCharacterMoveFunc)
    {
        return applyBaseCharacterMoveFunc(character);
    }
    else
    {
        return false;
    }
}

bool MovementClass::applySecondaryHorizontalMove(Character& character)
{
    if (applySecondaryHorizontalMoveFunc)
    {
        return applySecondaryHorizontalMoveFunc(character);
    }
    else
    {
        return false;
    }
}

bool MovementClass::applyVerticalMove(Character& character)
{
    if (applyVerticalMoveFunc)
    {
        return applyVerticalMoveFunc(character);
    }
    else
    {
        return false;
    }
}

void MovementClass::applyCollide(Character& character, Direction collideDir)
{
    if (applyCollideFunc)
    {
        return applyCollideFunc(character, collideDir);
    }
}

bool MovementClass::startJump(Character& character, bool spaceWasPressedLastFrame)
{
    if (startJumpFunc)
    {
        return startJumpFunc(character, spaceWasPressedLastFrame);
    }
    else
    {
        return false;
    }
}

void MovementClass::resetAllInternalFuncs()
{
    applyBaseCharacterMoveFunc = nullptr;
    applyVerticalMoveFunc = nullptr;
    applyCollideFunc = nullptr;
    startJumpFunc = nullptr;
}
