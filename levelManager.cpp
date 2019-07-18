#include <fstream>

#include "levelManager.hpp"
#include "blockManager.hpp"
#include "eventManager.hpp"
#include "utilities.hpp"
#include "global.hpp"

void levelManagerClass::setBlockHere(std::map<point, std::unique_ptr<blockClass>>& currentMap, std::string nameOfBlock, int xBlock, int yBlock)
{
    blockClass* block = blockManagerClass::createBlock(nameOfBlock);
    block->setPosition(xBlock * SIZE_BLOCK, yBlock * SIZE_BLOCK);
    currentMap[point(xBlock, yBlock)] = std::unique_ptr<blockClass>(block);
}

void levelManagerClass::loadLevelFromFile(levelInfo& currentLevel, std::string filePath)
{
    size_t spacePos;
    std::string currentLine;
    std::string currentType;
    std::string firstWordOfLine;
    std::ifstream file;
    file.open("resources/" + filePath);

    while(std::getline(file, currentLine))
    {
        spacePos = currentLine.find(' ');
        firstWordOfLine = currentLine.substr(0, spacePos);

        if(spacePos == std::string::npos)
        {
            currentLine.clear();
        }
        else
        {
            currentLine.erase(0, spacePos + 1);
        }

        if(firstWordOfLine == "GAME_VERSION")
        {
            currentLevel.initialGameVersion = utilitiesClass::stringToDouble(currentLine);
        }
        else if(firstWordOfLine == "NEXT_LEVEL")
        {
            currentLevel.nextLevelName = currentLine;
        }
        else if(firstWordOfLine == "SIZE_OF_LEVEL")
        {
            currentLevel.limitOfGame.top = 0;
            currentLevel.limitOfGame.left = 0;
            currentLevel.limitOfGame.width = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            currentLevel.limitOfGame.height = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
        }
        else if(firstWordOfLine == "PLAYER_POSITION")
        {
            currentLevel.playerStartPosition.x = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            currentLevel.playerStartPosition.y = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
        }
        else if(firstWordOfLine == "NEW_BLOCK")
        {
            std::string nameOfBlock = utilitiesClass::readFirstString(currentLine);
            int posX = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            int posY = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));

            setBlockHere(currentLevel.mapOfGame, nameOfBlock, posX, posY);
        }
        else if(firstWordOfLine == "NEW_EVENT")
        {
            std::string nameOfEvent = utilitiesClass::readFirstString(currentLine);
            int posX = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            int posY = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            int sizeX = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            int sizeY = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));

            currentLevel.listOfEvent.push_back(std::unique_ptr<eventClass>(
                    eventManagerClass::createEvent(nameOfEvent, sf::FloatRect(posX, posY, sizeX, sizeY), currentLine)));
        }
    }

    file.close();
}

void levelManagerClass::loadBasicLevelFromFile(basicLevelInfo& currentLevel, std::string filePath)
{
    size_t spacePos;
    std::string currentLine;
    std::string currentType;
    std::string firstWordOfLine;
    std::ifstream file;
    file.open("resources/" + filePath);

    while(std::getline(file, currentLine))
    {
        spacePos = currentLine.find(' ');
        firstWordOfLine = currentLine.substr(0, spacePos);

        if(spacePos == std::string::npos)
        {
            currentLine.clear();
        }
        else
        {
            currentLine.erase(0, spacePos + 1);
        }

        if(firstWordOfLine == "SIZE_OF_LEVEL")
        {
            currentLevel.limitOfGame.top = 0;
            currentLevel.limitOfGame.left = 0;
            currentLevel.limitOfGame.width = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            currentLevel.limitOfGame.height = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
        }
        else if(firstWordOfLine == "PLAYER_POSITION")
        {
            currentLevel.playerStartPosition.x = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            currentLevel.playerStartPosition.y = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
        }
        else if(firstWordOfLine == "NEW_BLOCK")
        {
            basicBlock newBlock;
            newBlock.name = utilitiesClass::readFirstString(currentLine);
            int posX = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));
            int posY = utilitiesClass::stringToInt(utilitiesClass::readFirstString(currentLine));

            newBlock.sprite.setSize(sf::Vector2f(SIZE_BLOCK, SIZE_BLOCK));
            newBlock.sprite.setPosition(SIZE_BLOCK * posX, SIZE_BLOCK * posY);
            newBlock.sprite.setFillColor(blockManagerClass::getColorOfBlock(newBlock.name));

            currentLevel.mapOfGame[point(posX, posY)] = std::move(newBlock);
        }
        else
        {
            std::string newLine = firstWordOfLine;

            if(!currentLine.empty())
            {
                newLine += " " + currentLine;
            }

            currentLevel.otherLines.push_back(newLine);
        }
    }

    file.close();
}

void levelManagerClass::saveBasicLevel(basicLevelInfo& currentLevel, std::string levelName)
{
    std::ofstream file;
    file.open("resources/" + levelName);

    file << "SIZE_OF_LEVEL " << currentLevel.limitOfGame.width << " " << currentLevel.limitOfGame.height << std::endl;
    file << "PLAYER_POSITION " << currentLevel.playerStartPosition.x << " " << currentLevel.playerStartPosition.y << std::endl;

    for(auto& currentLevelIte : currentLevel.mapOfGame)
    {
        file << "NEW_BLOCK " << currentLevelIte.second.name << " " << currentLevelIte.first.first << " " << currentLevelIte.first.second << std::endl;
    }

    for(std::string& line : currentLevel.otherLines)
    {
        file << line << std::endl;
    }

    file.close();
}
