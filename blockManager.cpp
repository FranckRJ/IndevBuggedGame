#include "blockManager.hpp"
#include "global.hpp"

std::unordered_map<std::string, std::pair<blockInfo, blockType>> blockManagerClass::listOfBlock;

void blockManagerClass::initialize()
{
    blockInfo baseInfo;
    blockType baseType;

    baseInfo.isFinishBlock = false;
    baseInfo.isSolidBlock = false;
    baseInfo.isOnlyOneBlock = false;
    baseInfo.isKillPlayerBlock = false;
    baseInfo.isForegroundBlock = false;

    baseType.colorOfBlock = sf::Color::Black;
    baseType.sizeOfBlock = sf::Vector2i(SIZE_BLOCK, SIZE_BLOCK);
    baseType.spaceOfBlock = sf::Vector2i(0, 0);

    {
        blockInfo info = baseInfo;
        blockType type = baseType;

        info.isFinishBlock = true;
        info.isOnlyOneBlock = true;
        info.isForegroundBlock = true;

        type.colorOfBlock = sf::Color::Red;

        listOfBlock["FINISH_BLOCK"] = std::pair<blockInfo, blockType>(info, type);
    }

    {
        blockInfo info = baseInfo;
        blockType type = baseType;

        info.isSolidBlock = true;

        type.colorOfBlock = sf::Color::Green;

        listOfBlock["COLLIDE_BLOCK"] = std::pair<blockInfo, blockType>(info, type);
    }

    {
        blockInfo info = baseInfo;
        blockType type = baseType;

        info.isKillPlayerBlock = true;
        info.isForegroundBlock = true;

        type.colorOfBlock = sf::Color(255, 140, 0);

        listOfBlock["LAVA_BLOCK"] = std::pair<blockInfo, blockType>(info, type);
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
        newBlock.sprite.setFillColor(infos->second.second.colorOfBlock);

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
        return infos->second.second.colorOfBlock;
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
