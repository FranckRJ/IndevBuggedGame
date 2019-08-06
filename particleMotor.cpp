#include <cstdlib>

#include "particleManager.hpp"
#include "particleMotor.hpp"

void ParticleMotor::update()
{
    for (auto thisParticle = mListOfParticle.begin(); thisParticle != mListOfParticle.end();)
    {
        (*thisParticle)->update();

        if ((*thisParticle)->getIsDead())
        {
            mListOfParticle.erase(thisParticle++);
            continue;
        }
        ++thisParticle;
    }
}

void ParticleMotor::draw(sf::RenderWindow& pWindow)
{
    for (const auto& thisParticle : mListOfParticle)
    {
        thisParticle->draw(pWindow);
    }
}

void ParticleMotor::addParticle(sf::Vector2f pAtThisPosition, int pParticleSpeed)
{
    auto addVerticalVelocity = -(rand() % 5);
    auto addHorizontalVelocity = (rand() % 5) - 2;

    mListOfParticle.emplace_back(ParticleManager::createParticle(
        "NORMAL_PARTICLE", sf::Color::Blue, sf::Vector2f{10.f, 10.f},
        sf::Vector2i{pParticleSpeed + addHorizontalVelocity, addVerticalVelocity}, pAtThisPosition));
}
