#include <stdexcept>

#include "particleManager.hpp"

void ParticleManager::initialize()
{
    {
        auto info = ParticleInfo{};

        info.verticalVelocity = -4;
        info.lostAlphaSpeed = 20;

        mListOfParticle["NORMAL_PARTICLE"] = info;
    }
}

std::unique_ptr<Particle> ParticleManager::createParticle(const std::string& pParticleName,
                                                          const sf::Color& pParticleColor,
                                                          const sf::Vector2f& pParticleSize,
                                                          const sf::Vector2i& pVelocity,
                                                          const sf::Vector2f& pBasePosition)
{
    auto infos = mListOfParticle.find(pParticleName);

    if (infos != mListOfParticle.end())
    {
        return std::make_unique<Particle>(infos->second, pParticleColor, pParticleSize, pVelocity, pBasePosition);
    }
    else
    {
        throw std::invalid_argument{"invalid particle name"};
    }
}
