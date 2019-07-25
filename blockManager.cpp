#include "blockManager.hpp"
#include "global.hpp"

std::unordered_map<std::string, std::pair<blockProperties, blockSprite>> blockManagerClass::listOfBlock;

void blockManagerClass::initialize()
{
    blockProperties baseInfo;
    blockSprite baseType;

    baseInfo.isFinishTrigger = false;
    baseInfo.isSolid = false;
    baseInfo.isTriggeredContinuously = true;
    baseInfo.isDeadlyToPlayer = false;
    baseInfo.isInForeground = false;

    baseType.color = sf::Color::Black;
    baseType.size = sf::Vector2i(SIZE_BLOCK, SIZE_BLOCK);
    baseType.margin = sf::Vector2i(0, 0);

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
        return new blockClass;
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
        return basicBlock();
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
        return sf::Color::Black;
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

    return basicBlock();
}

int blockManagerClass::getNumberOfBlock()
{
    return listOfBlock.size();
}
