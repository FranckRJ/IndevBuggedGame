#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

enum class Direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NONE
};

struct MoveInfos
{
    int speed = 0;
    int jumpPower = 0;
    double currentVerticalVelocity = 0;
    bool canJump = false;
    bool isInJump = false;
    bool canMoveIntentionally = false;
    // map des blocks qui forcent un deplacement avec la valeur des deplacements
};

class Character
{
public:
    virtual ~Character();
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hasEnterInCollide(Direction dir) = 0;
    virtual bool getIsDead();
    virtual sf::FloatRect getSpriteBox() = 0;
    virtual sf::FloatRect getCollideBox();
    virtual sf::Vector2i getPosition();
    virtual void setCanMoveIntentionally(bool newVal);
    virtual void setIsDead(bool newVal);
    virtual void setPosition(sf::Vector2i newPosition);
    virtual void setPosition(int newX, int newY);

protected:
    sf::Vector2i position;
    sf::Vector2i sizeOfCollideBox;
    MoveInfos infoForMove;
    bool isDead = false;
};

#endif
