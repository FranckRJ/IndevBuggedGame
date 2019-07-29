#include "particleManager.hpp"

void ParticleManager::initialize()
{
    ParticleInfo baseInfo;

    baseInfo.attractedByGravity = true;
    baseInfo.horizontalVelocity = 0;
    baseInfo.lifeTime = 0;
    baseInfo.verticalVelocity = 0;
    baseInfo.lostAlphaSpeed = 255;

    {
        ParticleInfo info = baseInfo;

        info.verticalVelocity = -4;
        info.lostAlphaSpeed = 20;

        listOfParticle["NORMAL_PARTICLE"] = info;
    }
}

Particle* ParticleManager::createParticle(std::string particleName, sf::Color particleColor, sf::Vector2f particleSize,
                                          sf::Vector2i velocity, sf::Vector2f basePosition)
{
    auto infos = listOfParticle.find(particleName);

    if (infos != listOfParticle.end())
    {
        return new Particle(infos->second, particleColor, particleSize, velocity, basePosition);
    }
    else
    {
        return new Particle;
    }
}
