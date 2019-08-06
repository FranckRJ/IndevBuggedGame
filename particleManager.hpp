#ifndef PARTICLEMANAGER_HPP
#define PARTICLEMANAGER_HPP

#include <map>
#include <memory>

#include "particle.hpp"

class ParticleManager
{
public:
    static void initialize();
    static std::unique_ptr<Particle> createParticle(const std::string& pParticleName, const sf::Color& pParticleColor,
                                                    const sf::Vector2f& pParticleSize, const sf::Vector2i& pVelocity,
                                                    const sf::Vector2f& pBasePosition);

private:
    static inline std::map<std::string, ParticleInfo> mListOfParticle;
};

#endif
