#ifndef STARTSCREENSTATE_HPP
#define STARTSCREENSTATE_HPP

#include <list>
#include <SFML/Graphics.hpp>

#include "gameState.hpp"

struct instructionStruct
{
    std::string typeOfInstruction;
    std::string infoForInstruction;
    instructionStruct(std::string baseType, std::string baseInfo) : typeOfInstruction(baseType), infoForInstruction(baseInfo) {}
};

class startScreenStateClass : public gameStateClass
{
public:
    startScreenStateClass();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
private:
    std::list<instructionStruct> listOfInstruction;
    sf::Text messageToShow;
    sf::Clock timer;
    bool waiting;
};

#endif
