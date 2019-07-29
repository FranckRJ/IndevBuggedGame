#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <SFML/System/Vector2.hpp>
#include <functional>

#include "character.hpp"
#include "versionNumber.hpp"

class MovementClass
{
public:
    void setFuncsForGameVersion(const VersionNumber& gameVersion);
    bool applyBaseCharacterMove(Character& character);
    bool applyVerticalMove(Character& character);
    void applyCollide(Character& character, Direction collideDIr);
    bool startJump(Character& character);

private:
    void resetAllInternalFuncs();

private:
    std::function<bool(Character&)> applyBaseCharacterMoveFunc;
    std::function<bool(Character&)> applyVerticalMoveFunc;
    std::function<void(Character&, Direction)> applyCollideFunc;
    std::function<bool(Character&)> startJumpFunc;
};

#endif
