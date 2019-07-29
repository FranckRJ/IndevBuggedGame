#ifndef EDITLEVELSTATE_HPP
#define EDITLEVELSTATE_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"
#include "levelManager.hpp"

class EditLevelState : public GameState
{
public:
    EditLevelState(std::string levelName);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void leftClickHere(int x, int y);
    void rightClickHere(int x, int y);
    void mouseMoveHere(int x, int y);
    void moveView(int x, int y);

private:
    sf::View view;
    BasicLevelInfo infoForLevel;
    BasicBlock currentBlock;
    std::string currentLevelName;
    sf::RectangleShape playerSprite;
};

#endif
