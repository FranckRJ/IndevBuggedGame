#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include <list>
#include <map>
#include <memory>

#include "block.hpp"
#include "event.hpp"
#include "versionNumber.hpp"

typedef std::pair<int, int> point;

struct levelInfo
{
    std::map<point, std::unique_ptr<blockClass>> mapOfGame;
    std::list<std::unique_ptr<eventClass>> listOfEvent;
    sf::IntRect limitOfGame;
    sf::Vector2i playerStartPosition;
    versionNumberClass initialGameVersion;
    std::string nextLevelName;
};

struct basicLevelInfo
{
    std::map<point, basicBlock> mapOfGame;
    sf::IntRect limitOfGame;
    sf::Vector2i playerStartPosition;
    std::list<std::string> otherLines;
};

class levelManagerClass
{
public:
    static void setBlockHere(std::map<point, std::unique_ptr<blockClass>>& currentMap, blockId idOfBlock, int xBlock,
                             int yBlock);
    static void loadLevelFromFile(levelInfo& currentLevel, std::string filePath);
    static void loadBasicLevelFromFile(basicLevelInfo& currentLevel, std::string filePath);
    static void saveBasicLevel(basicLevelInfo& currentLevel, std::string levelName);
};

#endif
