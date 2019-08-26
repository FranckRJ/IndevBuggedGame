#ifndef BLOCKMANAGER_HPP
#define BLOCKMANAGER_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "block.hpp"

class BlockManager
{
public:
    static void initialize();
    static std::unique_ptr<Block> createBlock(BlockId pId);
    static BasicBlock createBasicBlock(BlockId pId);
    static BasicBlock createNextBasicBlock(const BasicBlock& pBlock);
    static BasicBlock createPreviousBasicBlock(const BasicBlock& pBlock);
    static sf::Color getColorOfBlock(BlockId pId);
    static BlockInfos& getBlockInfos(BlockId pId);
    static constexpr std::size_t blockIdToNumber(BlockId pId);
    static constexpr BlockId numberToBlockId(std::size_t pNumber);
    static std::string blockIdToString(BlockId pId);
    static BlockId stringBlockId(std::string pStr);

private:
    static inline std::vector<BlockInfos> mListOfBlocks =
        std::vector<BlockInfos>(static_cast<std::size_t>(BlockId::NUMBER_OF_BLOCKS));
};

#endif
