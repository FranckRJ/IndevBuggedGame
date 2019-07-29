#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <set>

#include "blockId.hpp"
#include "direction.hpp"

class Character
{
public:
    virtual ~Character();
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hasEnterInCollide(Direction dir) = 0;
    virtual sf::Vector2i getPosition();
    virtual void setPosition(sf::Vector2i newPosition);
    virtual void setPosition(int newX, int newY);
    virtual void changePosition(int addX, int addY);
    virtual Direction getCurrentDirection() const;
    virtual Direction getMovedHorizontalDirection() const;
    virtual Direction getMovedVerticalDirection() const;
    virtual void setCurrentDirection(const Direction& value);
    virtual sf::FloatRect getSpriteBox() = 0;
    virtual sf::IntRect getCollideBox();
    virtual int getSpeed() const;
    virtual int getJumpPower() const;
    virtual double getCurrentVerticalVelocity() const;
    virtual void setCurrentVerticalVelocity(double value);
    virtual bool getCanJump() const;
    virtual void setCanJump(bool value);
    virtual bool getIsInJump() const;
    virtual void setIsInJump(bool value);
    virtual bool getCanMoveIntentionally() const;
    virtual void setCanMoveIntentionally(bool newVal);
    virtual bool getCanJumpIntentionally() const;
    virtual void setCanJumpIntentionally(bool value);
    virtual bool getIsDead() const;
    virtual void setIsDead(bool newVal);
    virtual bool getHasTriggeredFinishBlock() const;
    virtual void setHasTriggeredFinishBlock(bool value);
    virtual const std::set<BlockId> getSetOfBlocksAffectingMove() const;
    virtual void addToSetOfBlocksAffectingMove(BlockId newBlock);
    virtual void resetSetOfBlocksAffectingMove();

protected:
    sf::Vector2i position;
    Direction currentDirection;
    Direction movedHorizontalDirection = Direction::NONE;
    Direction movedVerticalDirection = Direction::NONE;
    sf::Vector2i sizeOfCollideBox;
    int speed = 0;
    int jumpPower = 0;
    double currentVerticalVelocity = 0;
    bool canJump = false;
    bool isInJump = false;
    bool canMoveIntentionally = false;
    bool canJumpIntentionally = false;
    bool isDead = false;
    bool hasTriggeredFinishBlock = false;
    std::set<BlockId> setOfBlocksAffectingMove;
};

#endif
