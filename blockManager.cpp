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
        auto properties = BlockProperties{};
        auto spriteInfos = BlockSprite{};

        properties.isFinishTrigger = true;
        properties.isTriggeredContinuously = false;
        properties.isInForeground = true;

        spriteInfos.color = sf::Color::Red;

        getBlockInfos(BlockId::FINISH_BLOCK) = {properties, spriteInfos};
    }

    {
        auto properties = BlockProperties{};
        auto spriteInfos = BlockSprite{};

        properties.isSolid = true;

        spriteInfos.color = sf::Color::Green;

        getBlockInfos(BlockId::COLLIDE_BLOCK) = {properties, spriteInfos};
    }

    {
        auto properties = BlockProperties{};
        auto spriteInfos = BlockSprite{};

        properties.isDeadlyToPlayer = true;
        properties.isInForeground = true;

        spriteInfos.color = sf::Color(255, 140, 0);

        getBlockInfos(BlockId::LAVA_BLOCK) = {properties, spriteInfos};
    }

    {
        auto properties = BlockProperties{};
        auto spriteInfos = BlockSprite{};

        properties.temporaryEffects = {{Character::Status::canMoveIntentionally, false},
                                       {Character::Status::isInFluid, true}};
        properties.addVelocityToCharacter = {5, 0};

        spriteInfos.color = sf::Color(138, 43, 226);

        getBlockInfos(BlockId::PUSH_RIGHT_BLOCK) = {properties, spriteInfos};
    }
}

std::unique_ptr<Block> BlockManager::createBlock(BlockId pId)
{
    const auto& infos = getBlockInfos(pId);

    return std::make_unique<Block>(infos.properties, infos.spriteInfos, pId);
}

BasicBlock BlockManager::createBasicBlock(BlockId pId)
{
    const auto& infos = getBlockInfos(pId);
    auto newBlock = BasicBlock{};

    newBlock.id = pId;
    newBlock.sprite.setSize(sf::Vector2f(SIZE_BLOCK, SIZE_BLOCK));
    newBlock.sprite.setFillColor(infos.spriteInfos.color);

    return newBlock;
}

BasicBlock BlockManager::createNextBasicBlock(const BasicBlock& pBlock)
{
    auto newBlockNumber = blockIdToNumber(pBlock.id) + 1;

    if (newBlockNumber >= blockIdToNumber(BlockId::NUMBER_OF_BLOCKS))
    {
        newBlockNumber = 0;
    }

    return createBasicBlock(numberToBlockId(newBlockNumber));
}

BasicBlock BlockManager::createPreviousBasicBlock(const BasicBlock& pBlock)
{
    auto newBlockNumber = blockIdToNumber(pBlock.id);

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

sf::Color BlockManager::getColorOfBlock(BlockId pId)
{
    const auto& infos = getBlockInfos(pId);

    return infos.spriteInfos.color;
}

BlockInfos& BlockManager::getBlockInfos(BlockId pId)
{
    const auto blockIdx = blockIdToNumber(pId);

    if (blockIdx < mListOfBlocks.size())
    {
        return mListOfBlocks[blockIdx];
    }
    else
    {
        throw std::invalid_argument("invalid block id");
    }
}

constexpr std::size_t BlockManager::blockIdToNumber(BlockId pId)
{
    return static_cast<std::size_t>(pId);
}

constexpr BlockId BlockManager::numberToBlockId(std::size_t pNumber)
{
    if (pNumber < blockIdToNumber(BlockId::NUMBER_OF_BLOCKS))
    {
        return static_cast<BlockId>(pNumber);
    }
    else
    {
        throw std::range_error("invalid block number");
    }
}

std::string BlockManager::blockIdToString(BlockId pId)
{
    const auto blockConv = blockIdToStringConvList.find(pId);

    if (blockConv != blockIdToStringConvList.end())
    {
        return blockConv->second;
    }
    else
    {
        throw std::invalid_argument("invalid block id");
    }
}

BlockId BlockManager::stringBlockId(std::string pStr)
{
    for (const auto& [idOfBlock, strOfBlock] : blockIdToStringConvList)
    {
        if (strOfBlock == pStr)
        {
            return idOfBlock;
        }
    }

    throw std::invalid_argument("invalid block name");
}
