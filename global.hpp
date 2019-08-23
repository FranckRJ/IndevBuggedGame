#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#define WIDTH_SCREEN 960
#define HEIGHT_SCREEN 540
#define SIZE_BLOCK 20
#define GRAVITY 1
#define SIZE_POLICE 30

#include <SFML/Graphics.hpp>
#include <random>

#include "gameStateStack.hpp"
#include "versionNumber.hpp"

namespace Global
{
    inline GameStateStack* activeGameStateStack;
    inline sf::Font font;
    inline std::random_device slow_random;
    inline std::mt19937 fast_random{slow_random()};
    inline std::uniform_int_distribution<int> randomPercentage{0, 100};
}; // namespace Global

#endif
