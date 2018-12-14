#include "particleManager.hpp"

std::unordered_map<std::string, particleInfo> particleManagerClass::listOfParticle;

void particleManagerClass::initialize()
{
    particleInfo baseInfo;

    baseInfo.attractedByGravity = true;
    baseInfo.horizontalVelocity = 0;
    baseInfo.lifeTime = 0;
    baseInfo.verticalVelocity = 0;
    baseInfo.lostAlphaSpeed = 255;

    {
        particleInfo info = baseInfo;

        info.verticalVelocity = -4;
        info.lostAlphaSpeed = 20;

        listOfParticle["NORMAL_PARTICLE"] = info;
    }
}

particleClass* particleManagerClass::createParticle(std::string particleName, sf::Color particleColor, sf::Vector2f particleSize, sf::Vector2i velocity, sf::Vector2f basePosition)
{
    auto infos = listOfParticle.find(particleName);

    if(infos != listOfParticle.end())
    {
        return new particleClass(infos->second, particleColor, particleSize, velocity, basePosition);
    }
    else
    {
        return new particleClass;
    }
}
