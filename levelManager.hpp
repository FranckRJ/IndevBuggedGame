#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include <list>
#include <map>
#include <memory>

#include "block.hpp"
#include "event.hpp"
#include "versionNumber.hpp"

typedef std::pair<int, int> Point;

struct LevelInfo
{
    std::map<Point, std::unique_ptr<Block>> mapOfGame;
    std::list<std::unique_ptr<Event>> listOfEvent;
    sf::IntRect limitOfGame;
    sf::Vector2i playerStartPosition;
    VersionNumber initialGameVersion;
    std::string nextLevelName;
};

struct BasicLevelInfo
{
    std::map<Point, BasicBlock> mapOfGame;
    sf::IntRect limitOfGame;
    sf::Vector2i playerStartPosition;
    std::list<std::string> otherLines;
};

class LevelManager
{
public:
    static void setBlockHere(std::map<Point, std::unique_ptr<Block>>& currentMap, BlockId idOfBlock, int xBlock,
                             int yBlock);
    static void loadLevelFromFile(LevelInfo& currentLevel, std::string filePath);
    static void loadBasicLevelFromFile(BasicLevelInfo& currentLevel, std::string filePath);
    static void saveBasicLevel(BasicLevelInfo& currentLevel, std::string levelName);
};

#endif
