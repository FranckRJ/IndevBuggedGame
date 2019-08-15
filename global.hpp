#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#define WIDTH_SCREEN 960
#define HEIGHT_SCREEN 540
#define SIZE_BLOCK 20
#define GRAVITY 1
#define SIZE_POLICE 30

#include <SFML/Graphics.hpp>

#include "gameStateStack.hpp"
#include "versionNumber.hpp"

namespace Global
{
    inline GameStateStack* activeGameStateStack;
    inline sf::Font font;
}; // namespace Global

#endif
