#ifndef MOVEMENT1_HPP
#define MOVEMENT1_HPP

#include "movement.hpp"

class movement1Class : public movementClass
{
public:
    sf::Vector2i moveCharacterTo(moveInfo& infoForMove, direction dir, sf::Vector2i position);
    sf::Vector2i applyGravity(moveInfo& infoForMove, sf::Vector2i position);
    void enterInCollide(moveInfo& infoForMove, direction dir);
    bool startJump(moveInfo& infoForMove);
};

#endif
