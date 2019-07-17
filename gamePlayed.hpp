#ifndef GAMEPLAYED_HPP
#define GAMEPLAYED_HPP

#include <SFML/Graphics.hpp>

#include "playerPlay.hpp"
#include "levelManager.hpp"

class gamePlayedClass
{
public:
    gamePlayedClass(std::string nameOfLevel);
    void update();
    void draw(sf::RenderWindow& window);
    void movePlayerTo(direction dir);
    void jumpPlayer();
    void checkCharacterInBorder(characterClass& character);
    bool checkCharacterCollideWithBlock(characterClass& character, direction dir, bool onlySolid = false);
    void checkCharacterCollideWithEvent(characterClass& character);
    void setCameraToCharacter(characterClass& character);
    void updateGameVersion();
private:
    playerPlayClass playerPlay;
    levelInfo infoForLevel;
    std::string currentLevelName;
    std::list<blockClass*> listOfForegroundBlock;
    sf::View view;
};

#endif
