#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <SFML/System/Vector2.hpp>
#include <functional>

#include "character.hpp"
#include "versionNumber.hpp"

class MovementClass
{
public:
    void setFuncsForGameVersion(const VersionNumber& pGameVersion);
    bool applyBaseCharacterMove(Character& pCharacter);
    bool applySecondaryHorizontalMove(Character& pCharacter);
    bool applyVerticalMove(Character& pCharacter);
    void applyCollide(Character& pCharacter, Direction pCollideDIr);
    bool startJump(Character& pCharacter, bool pSpaceWasPressedLastFrame);

private:
    void resetAllInternalFuncs();

private:
    std::function<bool(Character&)> mApplyBaseCharacterMoveFunc;
    std::function<bool(Character&)> mApplySecondaryHorizontalMoveFunc;
    std::function<bool(Character&)> mApplyVerticalMoveFunc;
    std::function<void(Character&, Direction)> mApplyCollideFunc;
    std::function<bool(Character&, bool)> mStartJumpFunc;
};

#endif
