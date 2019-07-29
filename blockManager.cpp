#include <map>
#include <stdexcept>

#include "blockManager.hpp"
#include "global.hpp"

namespace
{
    std::map<BlockId, std::string> blockIdToStringConvList = {{BlockId::COLLIDE_BLOCK, "COLLIDE_BLOCK"},
                                                              {BlockId::FINISH_BLOCK, "FINISH_BLOCK"},
                                                              {BlockId::LAVA_BLOCK, "LAVA_BLOCK"},
                                                              {BlockId::PUSH_RIGHT_BLOCK, "PUSH_RIGHT_BLOCK"}};
}

void BlockManager::initialize()
{
    {
        BlockProperties properties;
        BlockSprite spriteInfos;

        properties.isFinishTrigger = true;
        properties.isTriggeredContinuously = false;
        properties.isInForeground = true;

        spriteInfos.color = sf::Color::Red;

        getBlockInfos(BlockId::FINISH_BLOCK) = {properties, spriteInfos};
    }

    {
        BlockProperties properties;
        BlockSprite spriteInfos;

        properties.isSolid = true;

        spriteInfos.color = sf::Color::Green;

        getBlockInfos(BlockId::COLLIDE_BLOCK) = {properties, spriteInfos};
    }

    {
        BlockProperties properties;
        BlockSprite spriteInfos;

        properties.isDeadlyToPlayer = true;
        properties.isInForeground = true;

        spriteInfos.color = sf::Color(255, 140, 0);

        getBlockInfos(BlockId::LAVA_BLOCK) = {properties, spriteInfos};
    }

    {
        BlockProperties properties;
        BlockSprite spriteInfos;

        properties.doStopPlayerFromMoving = true;
        properties.affectCharacterMove = sf::Vector2i(5, 0);

        spriteInfos.color = sf::Color(138, 43, 226);

        getBlockInfos(BlockId::PUSH_RIGHT_BLOCK) = {properties, spriteInfos};
    }
}

Block* BlockManager::createBlock(BlockId id)
{
    BlockInfos& infos = getBlockInfos(id);

    return new Block(infos.properties, infos.spriteInfos, id);
}

BasicBlock BlockManager::createBasicBlock(BlockId id)
{
    BlockInfos& infos = getBlockInfos(id);
    BasicBlock newBlock;

    newBlock.id = id;
    newBlock.sprite.setSize(sf::Vector2f(SIZE_BLOCK, SIZE_BLOCK));
    newBlock.sprite.setFillColor(infos.spriteInfos.color);

    return newBlock;
}

BasicBlock BlockManager::createNextBasicBlock(const BasicBlock& block)
{
    std::size_t newBlockNumber = blockIdToNumber(block.id) + 1;

    if (newBlockNumber >= blockIdToNumber(BlockId::NUMBER_OF_BLOCKS))
    {
        newBlockNumber = 0;
    }

    return createBasicBlock(numberToBlockId(newBlockNumber));
}

BasicBlock BlockManager::createPreviousBasicBlock(const BasicBlock& block)
{
    std::size_t newBlockNumber = blockIdToNumber(block.id);

    if (newBlockNumber == 0)
    {
        newBlockNumber = blockIdToNumber(BlockId::NUMBER_OF_BLOCKS) - 1;
    }
    else
    {
        --newBlockNumber;
    }

    return createBasicBlock(numberToBlockId(newBlockNumber));
}

sf::Color BlockManager::getColorOfBlock(BlockId id)
{
    BlockInfos& infos = getBlockInfos(id);

    return infos.spriteInfos.color;
}

BlockInfos& BlockManager::getBlockInfos(BlockId id)
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

constexpr std::size_t BlockManager::blockIdToNumber(BlockId id)
{
    return static_cast<std::size_t>(id);
}

constexpr BlockId BlockManager::numberToBlockId(std::size_t number)
{
    if (number < blockIdToNumber(BlockId::NUMBER_OF_BLOCKS))
    {
        return static_cast<BlockId>(number);
    }
    else
    {
        throw std::range_error("invalid block number");
    }
}

std::string BlockManager::blockIdToString(BlockId id)
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

BlockId BlockManager::stringBlockId(std::string str)
{
    for (const auto& [idOfBlock, strOfBlock] : blockIdToStringConvList)
    {
        if (strOfBlock == str)
        {
            return idOfBlock;
        }
    }

    throw std::invalid_argument("invalid block name");
}
