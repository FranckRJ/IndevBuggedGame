#ifndef EDITLEVELSTATE_HPP
#define EDITLEVELSTATE_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "levelManager.hpp"

class editLevelStateClass : public gameStateClass
{
public:
    editLevelStateClass(std::string levelName);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void leftClickHere(int x, int y);
    void rightClickHere(int x, int y);
    void mouseMoveHere(int x, int y);
    void newIdForCurrentBlock();
    void moveView(int x, int y);
private:
    sf::View view;
    basicLevelInfo infoForLevel;
    basicBlock currentBlock;
    std::string currentLevelName;
    sf::RectangleShape playerSprite;
    int idCurrentBlock;
};

#endif
