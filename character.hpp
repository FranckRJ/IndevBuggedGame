#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

enum class direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NONE
};

struct moveInfo
{
    int speed = 0;
    int jumpPower = 0;
    double currentVerticalVelocity = 0;
    bool canJump = false;
    bool isInJump = false;
};

class characterClass
{
public:
    virtual ~characterClass();
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hasEnterInCollide(direction dir) = 0;
    virtual bool getIsDead() = 0;
    virtual sf::FloatRect getSpriteBox() = 0;
    virtual sf::FloatRect getCollideBox() = 0;
    virtual sf::Vector2i getPosition() = 0;
    virtual void setIsDead(bool newVal) = 0;
    virtual void setPosition(sf::Vector2i newPosition) = 0;
    virtual void setPosition(int newX, int newY) = 0;

protected:
    sf::Vector2i position;
    sf::Vector2i sizeOfCollideBox;
    moveInfo infoForMove;
    bool isDead = false;
};

#endif
