#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "character.hpp"

class movementClass
{
public:
    virtual sf::Vector2i moveCharacterTo(moveInfo& infoForMove, direction dir, sf::Vector2i position) = 0;
    virtual sf::Vector2i applyGravity(moveInfo& infoForMove, sf::Vector2i position) = 0;
    virtual void enterInCollide(moveInfo& infoForMove, direction dir) = 0;
    virtual bool startJump(moveInfo& infoForMove) = 0;
};

#endif
