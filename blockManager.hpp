#ifndef BLOCKMANAGER_HPP
#define BLOCKMANAGER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "block.hpp"

class blockManagerClass
{
public:
    static void initialize();
    static blockClass* createBlock(blockId id);
    static basicBlock createBasicBlock(blockId id);
    static basicBlock createNextBasicBlock(const basicBlock& block);
    static basicBlock createPreviousBasicBlock(const basicBlock& block);
    static sf::Color getColorOfBlock(blockId id);
    static blockInfos& getBlockInfos(blockId id);
    static constexpr std::size_t blockIdToNumber(blockId id);
    static constexpr blockId numberToBlockId(std::size_t number);
    static std::string blockIdToString(blockId id);
    static blockId stringBlockId(std::string str);

private:
    static inline std::vector listOfBlocks =
        std::vector<blockInfos>(static_cast<std::size_t>(blockId::NUMBER_OF_BLOCKS));
};

#endif
