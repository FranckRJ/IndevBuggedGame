#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <set>

#include "blockId.hpp"
#include "direction.hpp"

class Character
{
public:
    enum class Status
    {
        isDead,
        hasTriggeredFinishBlock,
        canMoveIntentionally,
        canJumpIntentionally,

    };

    Character() = default;

    Character(const Character& pOther) = delete;
    Character& operator=(const Character& pOther) = delete;

    Character(const Character&& pOther) = delete;
    Character& operator=(const Character&& pOther) = delete;

    virtual ~Character() = default;

    void update();
    void draw(sf::RenderWindow& pWindow);

    Direction movingDirection() const;
    Direction movedHorizontalDirection() const;
    Direction movedVerticalDirection() const;
    void setMovingDirection(Direction pDirection);
    void setMovedHorizontalDirection(Direction pDirection);
    void setMovedVerticalDirection(Direction pDirection);

    sf::FloatRect spriteBox() const;
    sf::IntRect collideBox() const;

    sf::Vector2i position() const;
    void setPosition(sf::Vector2i pPosition);
    void changePosition(sf::Vector2i pChangeToApply);

    double verticalVelocity() const;
    void setVerticalVelocity(double pVerticalVelocity);

    bool canJump() const;
    bool isInJump() const;
    void setCanJump(bool pCanJump);
    void setIsInJump(bool pIsInJump);

    bool hasStatus(Status pStatus) const;
    void setStatus(Status pStatus, bool pValue);
    void resetAllStatus();

    const std::set<BlockId> listOfBlocksAffectingMove() const;
    void addToListOfBlocksAffectingMove(BlockId pBlock);
    void resetListOfBlocksAffectingMove();

    int speed() const;
    int jumpPower() const;

    void hasEnterInCollide(Direction pDirection);

private:
    virtual void updateImpl() = 0;
    virtual void drawImpl(sf::RenderWindow& pWindow) = 0;

    virtual Direction movingDirectionImpl() const = 0;
    virtual Direction movedHorizontalDirectionImpl() const = 0;
    virtual Direction movedVerticalDirectionImpl() const = 0;
    virtual void setMovingDirectionImpl(Direction pDirection) = 0;
    virtual void setMovedHorizontalDirectionImpl(Direction pDirection) = 0;
    virtual void setMovedVerticalDirectionImpl(Direction pDirection) = 0;

    virtual sf::FloatRect spriteBoxImpl() const = 0;
    virtual sf::IntRect collideBoxImpl() const = 0;

    virtual sf::Vector2i positionImpl() const = 0;
    virtual void setPositionImpl(sf::Vector2i pPosition) = 0;
    virtual void changePositionImpl(sf::Vector2i pChangeToApply) = 0;

    virtual double verticalVelocityImpl() const = 0;
    virtual void setVerticalVelocityImpl(double pVerticalVelocity) = 0;

    virtual bool canJumpImpl() const = 0;
    virtual bool isInJumpImpl() const = 0;
    virtual void setCanJumpImpl(bool pCanJump) = 0;
    virtual void setIsInJumpImpl(bool pIsInJump) = 0;

    virtual bool hasStatusImpl(Status pStatus) const = 0;
    virtual void setStatusImpl(Status pStatus, bool pValue) = 0;
    virtual void resetAllStatusImpl() = 0;

    virtual const std::set<BlockId> listOfBlocksAffectingMoveImpl() const = 0;
    virtual void addToListOfBlocksAffectingMoveImpl(BlockId pBlock) = 0;
    virtual void resetListOfBlocksAffectingMoveImpl() = 0;

    virtual int speedImpl() const = 0;
    virtual int jumpPowerImpl() const = 0;

    virtual void hasEnterInCollideImpl(Direction pDirection) = 0;
};

class CharacterImpl : public Character
{
public:
    CharacterImpl(int pSpeed, int pJumpPower);

private:
    Direction movingDirectionImpl() const override;
    Direction movedHorizontalDirectionImpl() const override;
    Direction movedVerticalDirectionImpl() const override;
    void setMovingDirectionImpl(Direction pDirection) override;
    void setMovedHorizontalDirectionImpl(Direction pDirection) override;
    void setMovedVerticalDirectionImpl(Direction pDirection) override;

    sf::Vector2i positionImpl() const override;
    void setPositionImpl(sf::Vector2i pPosition) override;
    void changePositionImpl(sf::Vector2i pChangeToApply) override;

    double verticalVelocityImpl() const override;
    void setVerticalVelocityImpl(double pVerticalVelocity) override;

    bool canJumpImpl() const override;
    bool isInJumpImpl() const override;
    void setCanJumpImpl(bool pCanJump) override;
    void setIsInJumpImpl(bool pIsInJump) override;

    bool hasStatusImpl(Status pStatus) const override;
    void setStatusImpl(Status pStatus, bool pValue) override;
    void resetAllStatusImpl() override;

    const std::set<BlockId> listOfBlocksAffectingMoveImpl() const override;
    void addToListOfBlocksAffectingMoveImpl(BlockId pBlock) override;
    void resetListOfBlocksAffectingMoveImpl() override;

    int speedImpl() const override;
    int jumpPowerImpl() const override;

private:
    sf::Vector2i mPosition = {0, 0};
    Direction mMovingDirection = Direction::NONE;
    Direction mMovedHorizontalDirection = Direction::NONE;
    Direction mMovedVerticalDirection = Direction::NONE;
    const int mSpeed;
    const int mJumpPower;
    double mVerticalVelocity = 0;
    bool mCanJump = false;
    bool mIsInJump = false;
    std::set<Character::Status> mListOfStatus = {};
    std::set<BlockId> mListOfBlocksAffectingMove = {};
};

#endif
