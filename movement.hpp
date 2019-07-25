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
    sf::Vector2i moveCharacterTo(moveInfos& infoForMove, direction dir, sf::Vector2i position);
    sf::Vector2i applyGravity(moveInfos& infoForMove, sf::Vector2i position);
    void enterInCollide(moveInfos& infoForMove, direction dir);
    bool startJump(moveInfos& infoForMove);

private:
    void resetAllInternalFuncs();

private:
    std::function<sf::Vector2i(moveInfos&, direction, sf::Vector2i)> moveCharacterToFunc;
    std::function<sf::Vector2i(moveInfos&, sf::Vector2i)> applyGravityFunc;
    std::function<void(moveInfos&, direction)> enterInCollideFunc;
    std::function<bool(moveInfos&)> startJumpFunc;
};

#endif
