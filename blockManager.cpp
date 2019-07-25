#include <map>
#include <stdexcept>

#include "blockManager.hpp"
#include "global.hpp"

namespace
{
    std::map<blockId, std::string> blockIdToStringConvList = {{blockId::COLLIDE_BLOCK, "COLLIDE_BLOCK"},
                                                              {blockId::FINISH_BLOCK, "FINISH_BLOCK"},
                                                              {blockId::LAVA_BLOCK, "LAVA_BLOCK"},
                                                              {blockId::PUSH_RIGHT_BLOCK, "PUSH_RIGHT_BLOCK"}};
}

void blockManagerClass::initialize()
{
    {
        blockProperties properties;
        blockSprite spriteInfos;

        properties.isFinishTrigger = true;
        properties.isTriggeredContinuously = false;
        properties.isInForeground = true;

        spriteInfos.color = sf::Color::Red;

        getBlockInfos(blockId::FINISH_BLOCK) = {properties, spriteInfos};
    }

    {
        blockProperties properties;
        blockSprite spriteInfos;

        properties.isSolid = true;

        spriteInfos.color = sf::Color::Green;

        getBlockInfos(blockId::COLLIDE_BLOCK) = {properties, spriteInfos};
    }

    {
        blockProperties properties;
        blockSprite spriteInfos;

        properties.isDeadlyToPlayer = true;
        properties.isInForeground = true;

        spriteInfos.color = sf::Color(255, 140, 0);

        getBlockInfos(blockId::LAVA_BLOCK) = {properties, spriteInfos};
    }

    {
        blockProperties properties;
        blockSprite spriteInfos;

        properties.doStopPlayerFromMoving = true;

        spriteInfos.color = sf::Color(138, 43, 226);

        getBlockInfos(blockId::PUSH_RIGHT_BLOCK) = {properties, spriteInfos};
    }
}

blockClass* blockManagerClass::createBlock(blockId id)
{
    blockInfos& infos = getBlockInfos(id);

    return new blockClass(infos.properties, infos.spriteInfos);
}

basicBlock blockManagerClass::createBasicBlock(blockId id)
{
    blockInfos& infos = getBlockInfos(id);
    basicBlock newBlock;

    newBlock.id = id;
    newBlock.sprite.setSize(sf::Vector2f(SIZE_BLOCK, SIZE_BLOCK));
    newBlock.sprite.setFillColor(infos.spriteInfos.color);

    return newBlock;
}

basicBlock blockManagerClass::createNextBasicBlock(const basicBlock& block)
{
    std::size_t newBlockNumber = blockIdToNumber(block.id) + 1;

    if (newBlockNumber >= blockIdToNumber(blockId::NUMBER_OF_BLOCKS))
    {
        newBlockNumber = 0;
    }

    return createBasicBlock(numberToBlockId(newBlockNumber));
}

basicBlock blockManagerClass::createPreviousBasicBlock(const basicBlock& block)
{
    std::size_t newBlockNumber = blockIdToNumber(block.id);

    if (newBlockNumber == 0)
    {
        newBlockNumber = blockIdToNumber(blockId::NUMBER_OF_BLOCKS) - 1;
    }
    else
    {
        --newBlockNumber;
    }

    return createBasicBlock(numberToBlockId(newBlockNumber));
}

sf::Color blockManagerClass::getColorOfBlock(blockId id)
{
    blockInfos& infos = getBlockInfos(id);

    return infos.spriteInfos.color;
}

blockInfos& blockManagerClass::getBlockInfos(blockId id)
{
    std::size_t blockIdx = blockIdToNumber(id);

    if (blockIdx < listOfBlocks.size())
    {
        return listOfBlocks[blockIdx];
    }
    else
    {
        throw std::invalid_argument("invalid block id");
    }
}

constexpr std::size_t blockManagerClass::blockIdToNumber(blockId id)
{
    return static_cast<std::size_t>(id);
}

constexpr blockId blockManagerClass::numberToBlockId(std::size_t number)
{
    if (number < blockIdToNumber(blockId::NUMBER_OF_BLOCKS))
    {
        return static_cast<blockId>(number);
    }
    else
    {
        throw std::range_error("invalid block number");
    }
}

std::string blockManagerClass::blockIdToString(blockId id)
{
    const auto blockConv = blockIdToStringConvList.find(id);

    if (blockConv != blockIdToStringConvList.end())
    {
        return blockConv->second;
    }
    else
    {
        throw std::invalid_argument("invalid block id");
    }
}

blockId blockManagerClass::stringBlockId(std::string str)
{
    for (auto [idOfBlock, strOfBlock] : blockIdToStringConvList)
    {
        if (strOfBlock == str)
        {
            return idOfBlock;
        }
    }

    throw std::invalid_argument("invalid block name");
}
