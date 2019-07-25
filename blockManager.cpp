#include <stdexcept>

#include "blockManager.hpp"
#include "global.hpp"

void blockManagerClass::initialize()
{
    blockProperties baseInfo;
    blockSprite baseType;

    {
        blockProperties info = baseInfo;
        blockSprite type = baseType;

        info.isFinishTrigger = true;
        info.isTriggeredContinuously = false;
        info.isInForeground = true;

        type.color = sf::Color::Red;

        listOfBlock["FINISH_BLOCK"] = std::pair<blockProperties, blockSprite>(info, type);
    }

    {
        blockProperties info = baseInfo;
        blockSprite type = baseType;

        info.isSolid = true;

        type.color = sf::Color::Green;

        listOfBlock["COLLIDE_BLOCK"] = std::pair<blockProperties, blockSprite>(info, type);
    }

    {
        blockProperties info = baseInfo;
        blockSprite type = baseType;

        info.isDeadlyToPlayer = true;
        info.isInForeground = true;

        type.color = sf::Color(255, 140, 0);

        listOfBlock["LAVA_BLOCK"] = std::pair<blockProperties, blockSprite>(info, type);
    }
}

blockClass* blockManagerClass::createBlock(std::string blockName)
{
    auto infos = listOfBlock.find(blockName);

    if (infos != listOfBlock.end())
    {
        return new blockClass(infos->second.first, infos->second.second);
    }
    else
    {
        throw std::invalid_argument("invalid block name");
    }
}

basicBlock blockManagerClass::createBasicBlock(std::string blockName)
{
    auto infos = listOfBlock.find(blockName);

    if (infos != listOfBlock.end())
    {
        basicBlock newBlock;

        newBlock.name = infos->first;
        newBlock.sprite.setSize(sf::Vector2f(SIZE_BLOCK, SIZE_BLOCK));
        newBlock.sprite.setFillColor(infos->second.second.color);

        return newBlock;
    }
    else
    {
        throw std::invalid_argument("invalid block name");
    }
}

sf::Color blockManagerClass::getColorOfBlock(std::string blockName)
{
    auto infos = listOfBlock.find(blockName);

    if (infos != listOfBlock.end())
    {
        return infos->second.second.color;
    }
    else
    {
        throw std::invalid_argument("invalid block name");
    }
}

basicBlock blockManagerClass::getBasicBlockForBlockNumber(int number)
{
    int counter = 0;
    for (auto& listOfBlockIte : listOfBlock)
    {
        if (counter >= number)
        {
            return createBasicBlock(listOfBlockIte.first);
        }

        ++counter;
    }

    throw std::invalid_argument("invalid block number");
}

int blockManagerClass::getNumberOfBlock()
{
    return listOfBlock.size();
}
