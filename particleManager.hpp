#ifndef PARTICLEMANAGER_HPP
#define PARTICLEMANAGER_HPP

#include <unordered_map>

#include "particle.hpp"

class ParticleManager
{
public:
    static void initialize();
    static Particle* createParticle(std::string particleName, sf::Color particleColor, sf::Vector2f particleSize,
                                    sf::Vector2i velocity, sf::Vector2f basePosition);

private:
    static inline std::unordered_map<std::string, ParticleInfo> listOfParticle;
};

#endif
