#ifndef STARTSCREENSTATE_HPP
#define STARTSCREENSTATE_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "gameState.hpp"

struct InstructionInfos
{
    std::string typeOfInstruction;
    std::string infosForInstruction;
};

class StartScreenState : public GameState
{
public:
    StartScreenState();

private:
    void updateImpl(sf::RenderWindow& pWindow) override;
    void drawImpl(sf::RenderWindow& pWindow) const override;

private:
    std::list<InstructionInfos> mListOfInstructions;
    sf::Text mCurrentMessage;
    sf::Clock mTimer;
    bool mIsWaiting = false;
};

#endif
