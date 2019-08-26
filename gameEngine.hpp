#ifndef GAMEPLAYED_HPP
#define GAMEPLAYED_HPP

#include <SFML/Graphics.hpp>

#include "levelManager.hpp"
#include "player.hpp"

class GameEngine
{
public:
    GameEngine(std::string pNameOfLevel);
    void update();
    void draw(sf::RenderWindow& pWindow) const;
    void setPlayerDirection(Direction pDirection);
    void jumpPlayer(bool pSpaceWasPressedLastFrame);
    void checkCharacterInBorder(Character& pCharacter);
    void checkCharacterCollideWithBlock(Character& pCharacter, Direction pDirection, bool pOnlySolid = false);
    void checkCharacterCollideWithEvent(Character& pCharacter);
    void setCameraToCharacter(Character& pCharacter);
    void updateGameVersion();

private:
    VersionNumber mVersionOfGame = "1.0"_vn;
    Player mPlayer;
    LevelInfo mInfoForLevel;
    std::string mCurrentLevelName;
    std::list<Block*> mListOfForegroundBlock;
    sf::View mView;
};

#endif
