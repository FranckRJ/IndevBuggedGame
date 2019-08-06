#include "movement.hpp"
#include "blockManager.hpp"
#include "utilities.hpp"

namespace
{
    bool applyBaseCharacterMoveV1_0(Character& pCharacter)
    {
        if (pCharacter.hasStatus(Character::Status::canMoveIntentionally) &&
            pCharacter.movingDirection() != Direction::NONE)
        {
            if (pCharacter.movingDirection() == Direction::RIGHT)
            {
                pCharacter.changePosition({pCharacter.speed(), 0});
                return true;
            }
        }

        return false;
    }

    bool applyBaseCharacterMoveV1_1(Character& pCharacter)
    {
        if (pCharacter.hasStatus(Character::Status::canMoveIntentionally) &&
            pCharacter.movingDirection() != Direction::NONE)
        {
            if (pCharacter.movingDirection() == Direction::RIGHT)
            {
                pCharacter.changePosition({pCharacter.speed(), 0});
                return true;
            }
            else if (pCharacter.movingDirection() == Direction::LEFT)
            {
                pCharacter.changePosition({-pCharacter.speed(), 0});
                return true;
            }
        }

        return false;
    }

    bool applySecondaryHorizontalMoveV1_0(Character& pCharacter)
    {
        int changeToXPosition = 0;

        for (const BlockId& id : pCharacter.listOfBlocksAffectingMove())
        {
            changeToXPosition += BlockManager::getBlockInfos(id).properties.affectCharacterMove.x;
        }

        if (changeToXPosition != 0)
        {
            pCharacter.changePosition({changeToXPosition, 0});
            return true;
        }

        return false;
    }

    bool applyVerticalMoveV1_0(Character& pCharacter)
    {
        if (!Utilities::doubleIsNear(pCharacter.verticalVelocity(), 0.0))
        {
            pCharacter.changePosition({0, static_cast<int>(pCharacter.verticalVelocity())});
            return true;
        }

        return false;
    }

    void applyCollideV1_0(Character& pCharacter, Direction pCollideDir)
    {
        if (pCollideDir == Direction::UP || pCollideDir == Direction::DOWN)
        {
            if (pCharacter.verticalVelocity() > 100)
            {
                pCharacter.setVerticalVelocity(99);
            }
            else
            {
                pCharacter.setVerticalVelocity(0);
            }

            if (pCollideDir == Direction::DOWN)
            {
                pCharacter.setIsInJump(false);
            }
        }
        if (pCollideDir != Direction::NONE)
        {
            pCharacter.setCanJump(true);
        }
    }

    void applyCollideV1_4(Character& pCharacter, Direction pCollideDir)
    {
        if (pCollideDir == Direction::UP || pCollideDir == Direction::DOWN)
        {
            pCharacter.setVerticalVelocity(0);

            if (pCollideDir == Direction::DOWN)
            {
                pCharacter.setIsInJump(false);
            }

            pCharacter.setCanJump(true);
        }
    }

    void applyCollideV1_5(Character& pCharacter, Direction pCollideDir)
    {
        if (pCollideDir == Direction::UP || pCollideDir == Direction::DOWN)
        {
            pCharacter.setVerticalVelocity(0);

            if (pCollideDir == Direction::DOWN)
            {
                pCharacter.setCanJump(true);
                pCharacter.setIsInJump(false);
            }
        }
    }

    bool startJumpV1_0(Character& pCharacter, bool pSpaceWasPressedLastFrame)
    {
        (void)pCharacter;
        (void)pSpaceWasPressedLastFrame;
        return false;
    }

    bool startJumpV1_2(Character& pCharacter, bool pSpaceWasPressedLastFrame)
    {
        (void)pSpaceWasPressedLastFrame;

        if (pCharacter.hasStatus(Character::Status::canJumpIntentionally))
        {
            pCharacter.setVerticalVelocity(pCharacter.jumpPower());
            pCharacter.setCanJump(false);
            pCharacter.setIsInJump(true);
            return true;
        }

        return false;
    }

    bool startJumpV1_3(Character& pCharacter, bool pSpaceWasPressedLastFrame)
    {
        (void)pSpaceWasPressedLastFrame;

        if (pCharacter.hasStatus(Character::Status::canJumpIntentionally) && pCharacter.canJump())
        {
            pCharacter.setVerticalVelocity(pCharacter.jumpPower());
            pCharacter.setCanJump(false);
            pCharacter.setIsInJump(true);
            return true;
        }

        return false;
    }

    bool startJumpV1_5(Character& pCharacter, bool pSpaceWasPressedLastFrame)
    {
        if (pCharacter.hasStatus(Character::Status::canJumpIntentionally))
        {
            if (pCharacter.canJump())
            {
                pCharacter.setVerticalVelocity(pCharacter.jumpPower());
                pCharacter.setCanJump(false);
                pCharacter.setIsInJump(true);
                return true;
            }
            else if (!pSpaceWasPressedLastFrame)
            {
                pCharacter.setVerticalVelocity(0);
            }
        }

        return false;
    }

    bool startJumpV1_6(Character& pCharacter, bool pSpaceWasPressedLastFrame)
    {
        (void)pSpaceWasPressedLastFrame;

        if (pCharacter.hasStatus(Character::Status::canJumpIntentionally))
        {
            if (pCharacter.canJump())
            {
                pCharacter.setVerticalVelocity(pCharacter.jumpPower());
                pCharacter.setCanJump(false);
                pCharacter.setIsInJump(true);
                return true;
            }
        }

        return false;
    }
} // namespace

void MovementClass::setFuncsForGameVersion(const VersionNumber& pGameVersion)
{
    /* TODO: changer la maniere dont est gere gameVersion. */
    resetAllInternalFuncs();
    mApplyBaseCharacterMoveFunc = applyBaseCharacterMoveV1_0;
    mApplySecondaryHorizontalMoveFunc = applySecondaryHorizontalMoveV1_0;
    mApplyVerticalMoveFunc = applyVerticalMoveV1_0;
    mApplyCollideFunc = applyCollideV1_0;
    mStartJumpFunc = startJumpV1_0;

    if (pGameVersion >= "1.1"_vn)
    {
        mApplyBaseCharacterMoveFunc = applyBaseCharacterMoveV1_1;
    }
    if (pGameVersion >= "1.2"_vn)
    {
        mStartJumpFunc = startJumpV1_2;
    }
    if (pGameVersion >= "1.3"_vn)
    {
        mStartJumpFunc = startJumpV1_3;
    }
    if (pGameVersion >= "1.4"_vn)
    {
        mApplyCollideFunc = applyCollideV1_4;
    }
    if (pGameVersion >= "1.5"_vn)
    {
        mApplyCollideFunc = applyCollideV1_5;
        mStartJumpFunc = startJumpV1_5;
    }
    if (pGameVersion >= "1.6"_vn)
    {
        mStartJumpFunc = startJumpV1_6;
    }
}

bool MovementClass::applyBaseCharacterMove(Character& pCharacter)
{
    if (mApplyBaseCharacterMoveFunc)
    {
        return mApplyBaseCharacterMoveFunc(pCharacter);
    }
    else
    {
        return false;
    }
}

bool MovementClass::applySecondaryHorizontalMove(Character& pCharacter)
{
    if (mApplySecondaryHorizontalMoveFunc)
    {
        return mApplySecondaryHorizontalMoveFunc(pCharacter);
    }
    else
    {
        return false;
    }
}

bool MovementClass::applyVerticalMove(Character& pCharacter)
{
    if (mApplyVerticalMoveFunc)
    {
        return mApplyVerticalMoveFunc(pCharacter);
    }
    else
    {
        return false;
    }
}

void MovementClass::applyCollide(Character& pCharacter, Direction pCollideDIr)
{
    if (mApplyCollideFunc)
    {
        return mApplyCollideFunc(pCharacter, pCollideDIr);
    }
}

bool MovementClass::startJump(Character& pCharacter, bool pSpaceWasPressedLastFrame)
{
    if (mStartJumpFunc)
    {
        return mStartJumpFunc(pCharacter, pSpaceWasPressedLastFrame);
    }
    else
    {
        return false;
    }
}

void MovementClass::resetAllInternalFuncs()
{
    mApplyBaseCharacterMoveFunc = nullptr;
    mApplyVerticalMoveFunc = nullptr;
    mApplyCollideFunc = nullptr;
    mStartJumpFunc = nullptr;
}
