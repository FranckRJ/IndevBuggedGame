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
    sf::Vector2i moveCharacterTo(MoveInfos& infoForMove, Direction dir, sf::Vector2i position);
    sf::Vector2i applyGravity(MoveInfos& infoForMove, sf::Vector2i position);
    void enterInCollide(MoveInfos& infoForMove, Direction dir);
    bool startJump(MoveInfos& infoForMove);

private:
    void resetAllInternalFuncs();

private:
    std::function<sf::Vector2i(MoveInfos&, Direction, sf::Vector2i)> moveCharacterToFunc;
    std::function<sf::Vector2i(MoveInfos&, sf::Vector2i)> applyGravityFunc;
    std::function<void(MoveInfos&, Direction)> enterInCollideFunc;
    std::function<bool(MoveInfos&)> startJumpFunc;
};

#endif
