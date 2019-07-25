#ifndef BLOCKMANAGER_HPP
#define BLOCKMANAGER_HPP

#include "block.hpp"

class blockManagerClass
{
public:
    static void initialize();
    static blockClass* createBlock(std::string blockName);
    static basicBlock createBasicBlock(std::string blockName);
    static sf::Color getColorOfBlock(std::string blockName);
    static basicBlock getBasicBlockForBlockNumber(int number);
    static int getNumberOfBlock();

private:
    static inline std::unordered_map<std::string, std::pair<blockProperties, blockSprite>> listOfBlock;
};

#endif
