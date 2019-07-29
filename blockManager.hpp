#ifndef BLOCKMANAGER_HPP
#define BLOCKMANAGER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "block.hpp"

class BlockManager
{
public:
    static void initialize();
    static Block* createBlock(BlockId id);
    static BasicBlock createBasicBlock(BlockId id);
    static BasicBlock createNextBasicBlock(const BasicBlock& block);
    static BasicBlock createPreviousBasicBlock(const BasicBlock& block);
    static sf::Color getColorOfBlock(BlockId id);
    static BlockInfos& getBlockInfos(BlockId id);
    static constexpr std::size_t blockIdToNumber(BlockId id);
    static constexpr BlockId numberToBlockId(std::size_t number);
    static std::string blockIdToString(BlockId id);
    static BlockId stringBlockId(std::string str);

private:
    static inline std::vector listOfBlocks =
        std::vector<BlockInfos>(static_cast<std::size_t>(BlockId::NUMBER_OF_BLOCKS));
};

#endif
