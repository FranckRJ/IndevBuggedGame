#ifndef GAMEPLAYED_HPP
#define GAMEPLAYED_HPP

#include <SFML/Graphics.hpp>

#include "levelManager.hpp"
#include "player.hpp"

class GameEngine
{
public:
    GameEngine(std::string nameOfLevel);
    void update();
    void draw(sf::RenderWindow& window);
    void setPlayerDirection(Direction dir);
    void jumpPlayer(bool spaceWasPressedLastFrame);
    void checkCharacterInBorder(Character& character);
    void checkCharacterCollideWithBlock(Character& character, Direction dir, bool onlySolid = false);
    void checkCharacterCollideWithEvent(Character& character);
    void setCameraToCharacter(Character& character);
    void updateGameVersion();

private:
    Player player;
    LevelInfo infoForLevel;
    std::string currentLevelName;
    std::list<Block*> listOfForegroundBlock;
    sf::View view;
};

#endif
