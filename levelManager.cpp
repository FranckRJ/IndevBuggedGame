#include <fstream>

#include "blockManager.hpp"
#include "eventManager.hpp"
#include "global.hpp"
#include "levelManager.hpp"
#include "utilities.hpp"

void LevelManager::setBlockHere(std::map<Point, std::unique_ptr<Block>>& currentMap, BlockId idOfBlock, int xBlock,
                                int yBlock)
{
    Block* block = BlockManager::createBlock(idOfBlock);
    block->setPosition({xBlock * SIZE_BLOCK, yBlock * SIZE_BLOCK});
    currentMap[Point(xBlock, yBlock)] = std::unique_ptr<Block>(block);
}

void LevelManager::loadLevelFromFile(LevelInfo& currentLevel, std::string filePath)
{
    size_t spacePos;
    std::string currentLine;
    std::string currentType;
    std::string firstWordOfLine;
    std::ifstream file;
    file.open("resources/" + filePath);

    while (std::getline(file, currentLine))
    {
        spacePos = currentLine.find(' ');
        firstWordOfLine = currentLine.substr(0, spacePos);

        if (spacePos == std::string::npos)
        {
            currentLine.clear();
        }
        else
        {
            currentLine.erase(0, spacePos + 1);
        }

        if (firstWordOfLine == "GAME_VERSION")
        {
            currentLevel.initialGameVersion = VersionNumber(currentLine);
        }
        else if (firstWordOfLine == "NEXT_LEVEL")
        {
            currentLevel.nextLevelName = currentLine;
        }
        else if (firstWordOfLine == "SIZE_OF_LEVEL")
        {
            currentLevel.limitOfGame.top = 0;
            currentLevel.limitOfGame.left = 0;
            currentLevel.limitOfGame.width = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            currentLevel.limitOfGame.height = Utilities::stringToInt(Utilities::readFirstString(currentLine));
        }
        else if (firstWordOfLine == "PLAYER_POSITION")
        {
            currentLevel.playerStartPosition.x = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            currentLevel.playerStartPosition.y = Utilities::stringToInt(Utilities::readFirstString(currentLine));
        }
        else if (firstWordOfLine == "NEW_BLOCK")
        {
            BlockId idOfBlock = BlockManager::stringBlockId(Utilities::readFirstString(currentLine));
            int posX = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            int posY = Utilities::stringToInt(Utilities::readFirstString(currentLine));

            setBlockHere(currentLevel.mapOfGame, idOfBlock, posX, posY);
        }
        else if (firstWordOfLine == "NEW_EVENT")
        {
            std::string nameOfEvent = Utilities::readFirstString(currentLine);
            int posX = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            int posY = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            int sizeX = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            int sizeY = Utilities::stringToInt(Utilities::readFirstString(currentLine));

            currentLevel.listOfEvent.push_back(std::unique_ptr<EventClass>(
                EventManager::createEvent(nameOfEvent, sf::IntRect(posX, posY, sizeX, sizeY), currentLine)));
        }
    }

    file.close();
}

void LevelManager::loadBasicLevelFromFile(BasicLevelInfo& currentLevel, std::string filePath)
{
    size_t spacePos;
    std::string currentLine;
    std::string currentType;
    std::string firstWordOfLine;
    std::ifstream file;
    file.open("resources/" + filePath);

    while (std::getline(file, currentLine))
    {
        spacePos = currentLine.find(' ');
        firstWordOfLine = currentLine.substr(0, spacePos);

        if (spacePos == std::string::npos)
        {
            currentLine.clear();
        }
        else
        {
            currentLine.erase(0, spacePos + 1);
        }

        if (firstWordOfLine == "SIZE_OF_LEVEL")
        {
            currentLevel.limitOfGame.top = 0;
            currentLevel.limitOfGame.left = 0;
            currentLevel.limitOfGame.width = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            currentLevel.limitOfGame.height = Utilities::stringToInt(Utilities::readFirstString(currentLine));
        }
        else if (firstWordOfLine == "PLAYER_POSITION")
        {
            currentLevel.playerStartPosition.x = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            currentLevel.playerStartPosition.y = Utilities::stringToInt(Utilities::readFirstString(currentLine));
        }
        else if (firstWordOfLine == "NEW_BLOCK")
        {
            BasicBlock newBlock;
            newBlock.id = BlockManager::stringBlockId(Utilities::readFirstString(currentLine));
            int posX = Utilities::stringToInt(Utilities::readFirstString(currentLine));
            int posY = Utilities::stringToInt(Utilities::readFirstString(currentLine));

            newBlock.sprite.setSize(sf::Vector2f(SIZE_BLOCK, SIZE_BLOCK));
            newBlock.sprite.setPosition(SIZE_BLOCK * posX, SIZE_BLOCK * posY);
            newBlock.sprite.setFillColor(BlockManager::getColorOfBlock(newBlock.id));

            currentLevel.mapOfGame[Point(posX, posY)] = std::move(newBlock);
        }
        else
        {
            std::string newLine = firstWordOfLine;

            if (!currentLine.empty())
            {
                newLine += " " + currentLine;
            }

            currentLevel.otherLines.push_back(newLine);
        }
    }

    file.close();
}

void LevelManager::saveBasicLevel(BasicLevelInfo& currentLevel, std::string levelName)
{
    std::ofstream file;
    file.open("resources/" + levelName);

    file << "SIZE_OF_LEVEL " << currentLevel.limitOfGame.width << " " << currentLevel.limitOfGame.height << std::endl;
    file << "PLAYER_POSITION " << currentLevel.playerStartPosition.x << " " << currentLevel.playerStartPosition.y
         << std::endl;

    for (auto& currentLevelIte : currentLevel.mapOfGame)
    {
        file << "NEW_BLOCK " << BlockManager::blockIdToString(currentLevelIte.second.id) << " "
             << currentLevelIte.first.first << " " << currentLevelIte.first.second << std::endl;
    }

    for (std::string& line : currentLevel.otherLines)
    {
        file << line << std::endl;
    }

    file.close();
}
