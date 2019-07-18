#ifndef STARTSCREENSTATE_HPP
#define STARTSCREENSTATE_HPP

#include <list>
#include <SFML/Graphics.hpp>

#include "gameState.hpp"

struct instructionStruct
{
    std::string typeOfInstruction;
    std::string infosForInstruction;
    instructionStruct(std::string baseType, std::string baseInfo) : typeOfInstruction(baseType), infosForInstruction(baseInfo) {}
};

class startScreenStateClass : public gameStateClass
{
public:
    startScreenStateClass();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
private:
    std::list<instructionStruct> listOfInstructions;
    sf::Text currentMessage;
    sf::Clock timer;
    bool isWaiting = false;
};

#endif
