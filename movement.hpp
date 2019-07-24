#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <SFML/System/Vector2.hpp>
#include <functional>

#include "character.hpp"
#include "versionNumber.hpp"

class movementClass
{
public:
    void setFuncsForGameVersion(const versionNumberClass& gameVersion);
    sf::Vector2i moveCharacterTo(moveInfo& infoForMove, direction dir, sf::Vector2i position);
    sf::Vector2i applyGravity(moveInfo& infoForMove, sf::Vector2i position);
    void enterInCollide(moveInfo& infoForMove, direction dir);
    bool startJump(moveInfo& infoForMove);

private:
    void resetAllInternalFuncs();

private:
    std::function<sf::Vector2i(moveInfo&, direction, sf::Vector2i)> moveCharacterToFunc;
    std::function<sf::Vector2i(moveInfo&, sf::Vector2i)> applyGravityFunc;
    std::function<void(moveInfo&, direction)> enterInCollideFunc;
    std::function<bool(moveInfo&)> startJumpFunc;
};

#endif
