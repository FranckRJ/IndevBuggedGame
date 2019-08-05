#ifndef STARTSCREENSTATE_HPP
#define STARTSCREENSTATE_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "gameState.hpp"

struct InstructionInfos
{
    std::string typeOfInstruction;
    std::string infosForInstruction;
    InstructionInfos(std::string baseType, std::string baseInfo)
        : typeOfInstruction(baseType), infosForInstruction(baseInfo)
    {
    }
};

class StartScreenState : public GameState
{
public:
    StartScreenState();

private:
    void updateImpl(sf::RenderWindow& window) override;
    void drawImpl(sf::RenderWindow& window) override;

private:
    std::list<InstructionInfos> listOfInstructions;
    sf::Text currentMessage;
    sf::Clock timer;
    bool isWaiting = false;
};

#endif
