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

struct moveInfos
{
    int speed = 0;
    int jumpPower = 0;
    double currentVerticalVelocity = 0;
    bool canJump = false;
    bool isInJump = false;
    bool canMoveIntentionally = false;
};

class characterClass
{
public:
    virtual ~characterClass();
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hasEnterInCollide(direction dir) = 0;
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
    moveInfos infoForMove;
    bool isDead = false;
};

#endif
